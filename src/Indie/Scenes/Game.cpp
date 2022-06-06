/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include "Crate.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Round.hpp"
#include "Wall.hpp"
#include "raylib.h"

Game::Game(GameData* data, Core& core_ref) noexcept
    : Scene()
    , data_(data)
    , chrono_(std::make_unique<Timer>(data_->timeParty))
    , isHurry(false)
    , nbBlockPlaced(0)
    , loop_music_(GAME_MUSIC)
    , hurry_music_(HURRY_MUSIC)
    , core_entry_(core_ref)
    , background_color_(Colors::C_BLACK)
    , startSound_(START)
    , hurryUpSound_(HURRY_UP)
{
    createMap();
    startSound_.play();
    hurryUpSound_.setVolume(0.7f);
}

Game::~Game() noexcept
{
    loop_music_.unload();
    hurry_music_.unload();
    startSound_.unload();
    hurryUpSound_.unload();
}

void Game::switchAction() noexcept
{
    for (auto& player : data_->players) {
        if (player->getEntityType() != EntityType::E_PLAYER) continue;
        ((std::unique_ptr<Player>&)player)->setBombArray(&entities_);
    }
}

void Game::playMusic() noexcept
{
    loop_music_.play();
}

MusicManager Game::getMusicManager() const noexcept
{
    if (loop_music_.isPlaying()) return loop_music_;
    else
        return hurry_music_;
}

void Game::resetCameraman(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void Game::display3D() noexcept
{
    DrawPlane({ 0.0f, 0.0f, 1.0f }, { 13.0f, 11.0f }, { 0, 207, 68, 255 });
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if (z % 2 == 0 && x % 2 == 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
            if (z % 2 != 0 && x % 2 != 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
        }

    for (auto& player : data_->players) player->Display();
    for (auto& entity : entities_) entity->Display();
}

void Game::display2D() noexcept
{
    FpsHandler::draw(50, 50);

    if (!chrono_->timerDone()) {
        auto time = std::to_string(int(round(chrono_->getTime())));
        DrawText(time.data(), GetScreenWidth() / 2 - time.size(), 10, 30, WHITE);
    }

    if (isHurry) { DrawText("Hurry up !", HurryUpX, GetScreenHeight() / 2 - 60, 100, RED); }

    for (size_t i = 0; i != data_->players.size(); i++) {
        data_->sprites[i]->draw();
        auto player = (&(std::unique_ptr<Player>&)(data_->players[i]))->get();

        std::string speed = std::to_string(player->getSpeed());
        speed             = speed.substr(0, speed.find(".") + 2);
        std::string stats = std::to_string(player->getNbBomb()) + ", "
                            + std::to_string(player->getBombSize()) + ", " + speed;
        int size    = stats.size() / 1.4 * 20;
        int xPos[4] = { 55, GetScreenWidth() - size, GetScreenWidth() - size, 55 };
        int yPos[4] = { 28, GetScreenHeight() - 30, 28, GetScreenHeight() - 30 };

        DrawText(stats.c_str(), xPos[i], yPos[i], 20, WHITE);
    }
}

void Game::action(Cameraman& camera, MouseHandler mouse_) noexcept
{
    DestroyPool();
    CollisionPool();
    chrono_->updateTimer();

    int alive = 0;
    for (auto& player : data_->players)
        if (player->getEnabledValue()) alive++;
    if (alive == 1 || alive == 0) { core_entry_.switchScene(SceneType::ENDGAME); }

    for (auto& player : data_->players) player->Update();
    for (auto& entity : entities_) entity->Update();

    if (!camera.getIsMoving()) camera.lookBetweenEntity(data_->players);

    // Modificatoin de nombre de joueur à l'écran
    if (IsKeyPressed(KEY_C) && data_->nbPlayer < 4) {
        data_->nbPlayer++;
        auto tempPlayer = std::make_unique<Player>(data_->nbPlayer - 1, data_);
        tempPlayer->setBombArray(&entities_);
        data_->players.emplace_back(std::move(tempPlayer));
    }
    if (IsKeyPressed(KEY_V) && data_->nbPlayer > 1) {
        data_->nbPlayer--;
        data_->players.erase(data_->players.begin() + data_->nbPlayer);
    }

    // Activation du Hurry Up !
    if (int(round(chrono_->getTime())) <= 55 && !isHurry) {
        isHurry            = true;
        lastTimeBlockPlace = chrono_->getTime();
        HurryUpX           = GetScreenWidth() - 100;
        hurryUpSound_.play();
    }
    hurryUp();

    int xPos[4] = { 10, GetScreenWidth() - 50, GetScreenWidth() - 50, 10 };
    int yPos[4] = { 10, GetScreenHeight() - 50, 10, GetScreenHeight() - 50 };
    for (size_t i = 0; i != data_->players.size(); i++) data_->sprites[i]->setPos(xPos[i], yPos[i]);
}

void Game::DestroyPool() noexcept
{
    // suppression des entités désactivées
    size_t len = entities_.size();
    for (size_t i = 0; i != len; i++) {
        if (!entities_[i]->getEnabledValue()) {
            entities_.erase(entities_.begin() + i);
            len--;
            i--;
        }
    }
}

void Game::CollisionPool() noexcept
{
    // Collisions jouers/entités
    for (auto& player : data_->players) {
        for (auto& entity : entities_) {
            auto hitbox       = player->getComponent<BoxCollider>();
            auto other_hitbox = entity->getComponent<BoxCollider>();
            if (hitbox == std::nullopt || other_hitbox == std::nullopt) continue;
            if (hitbox->get().isColliding(other_hitbox->get())) {
                player->OnCollisionEnter(entity);
                entity->OnCollisionEnter(player);
            }
        }
    }
    for (auto& entity1 : entities_) {
        for (auto& entity : entities_) {
            auto hitbox       = entity1->getComponent<BoxCollider>();
            auto other_hitbox = entity->getComponent<BoxCollider>();
            if (hitbox == std::nullopt || other_hitbox == std::nullopt) continue;
            if (!hitbox->get().getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
            if (entity1 == entity) continue;
            if (hitbox->get().isColliding(other_hitbox->get())) {
                entity1->OnCollisionEnter(entity);
                entity->OnCollisionEnter(entity1);
            }
        }
    }
}

void Game::createMap() noexcept
{
    Vector3 vectorTemp;

    // Ajout des murs autour de la carte
    for (int z = -5; z < 8; z++)
        for (int x = -7; x < 8; x++)
            if (x == -7 || x == 7 || z == -5 || z == 7) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                entities_.emplace_back(
                    std::make_unique<Wall>(vectorTemp, &data_->models[(int)ModelType::M_WALL]));
            }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++)
            if (x % 2 != 0 && z % 2 != 0) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                entities_.emplace_back(std::make_unique<Wall>(
                    vectorTemp, &data_->models[static_cast<int>(ModelType::M_WALL)]));
            }

    // Génération des boites
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if ((x == -6 && z == -4) || (x == 6 && z == -4) || (x == -6 && z == 6)
                || (x == 6 && z == 6) || (x == -6 && z == -3) || (x == 6 && z == -3)
                || (x == -6 && z == 5) || (x == 6 && z == 5) || (x == -5 && z == -4)
                || (x == 5 && z == -4) || (x == -5 && z == 6) || (x == 5 && z == 6))
                continue;

            Vector3 vectorTemp = { x * 1.0f, 0.01f, z * 1.0f };

            bool spawnCrate = true;
            for (auto& entity : entities_) {
                auto transform = entity->getComponent<Transform3D>();
                if (transform == std::nullopt) continue;

                Vector3 pos = transform->get().getPosition();
                if (pos.x == vectorTemp.x && pos.z == vectorTemp.z) {
                    spawnCrate = false;
                    break;
                }
            }
            if (rand() % 100 < 80 && spawnCrate)
                entities_.emplace_back(std::make_unique<Crate>(vectorTemp,
                    &data_->models[static_cast<int>(ModelType::M_CRATE)],
                    data_,
                    &entities_));
        }
}

void Game::hurryUp() noexcept
{
    if (!isHurry) return;

    float time = chrono_->getTime();

    if (lastTimeBlockPlace - time >= 0.37f) {
        Vector3 vectorTemp;

        if (direction == Direction::UP) {
            z--;
            if (z == minZ) {
                direction = Direction::RIGHT;
                minZ++;
                x--;
            }
        }
        if (direction == Direction::RIGHT) {
            x++;
            if (x == maxX) {
                direction = Direction::DOWN;
                maxX--;
                z--;
            }
        }
        if (direction == Direction::DOWN) {
            z++;
            if (z == maxZ) {
                direction = Direction::LEFT;
                maxZ--;
                x++;
            }
        }
        if (direction == Direction::LEFT) {
            x--;
            if (x == minX) {
                direction = Direction::UP;
                minX++;
            }
        }

        vectorTemp = { x * 1.0f, 5.0f, z * 1.0f };
        entities_.emplace_back(std::make_unique<Wall>(
            vectorTemp, &data_->models[static_cast<int>(ModelType::M_WALL)]));
        lastTimeBlockPlace = chrono_->getTime();
        nbBlockPlaced++;
    }

    HurryUpX -= 500.0f * GetFrameTime();

    if (nbBlockPlaced >= 80 && isHurry) isHurry = false;
}

Vector3 Game::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 Game::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 Game::getCameraUp() const noexcept
{
    return (camera_up_);
}

ColorManager Game::getBackgroundColor() const noexcept
{
    return (background_color_);
}