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
#include "Shortcuts.hpp"
#include "Wall.hpp"
#include "raylib.h"

Game::Game(GameData* data, Core& core_ref) noexcept
    : Scene()
    , data_(data)
    , chrono_(NEW_TIMER(data_->timeParty))
    , isHurry(false)
    , nbBlockPlaced(0)
    , loop_music_(GAME_MUSIC)
    , core_entry_(core_ref)
{
    // Assignation des bombes aux joueurs
    for (auto& player : data_->players) {
        if (player->getEntityType() != EntityType::E_PLAYER) continue;
        ((std::unique_ptr<Player>&)player)->setBombArray(&entities_);
    }
    createMap();
}

Game::~Game() noexcept
{
    loop_music_.unload();
}

void Game::playMusic() const noexcept
{
    loop_music_.play();
}

MusicManager Game::getMusicManager() const noexcept
{
    return (loop_music_);
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void Game::display3D() noexcept
{
    DrawPlane({ 0.0f, 0.0f, 1.0f }, { 13.0f, 11.0f }, { 0, 207, 68, 255 });
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if (z % 2 == 0 && x % 2 == 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f },
                    { 1.0f, 1.0f },
                    { 0, 181, 48, 255 });
            if (z % 2 != 0 && x % 2 != 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f },
                    { 1.0f, 1.0f },
                    { 0, 181, 48, 255 });
        }

    for (auto& player : data_->players) player->Display();
    for (auto& entity : entities_) entity->Display();
}

void Game::display2D() noexcept
{
    DrawFPS(10, 10);
    DrawText("Game", 10, 30, 20, GREEN);
    if (chrono_->timerDone()) DrawText("Party end", 10, 50, 20, BLUE);
    else
        DrawText(std::to_string(int(round(chrono_->getTime()))).data(),
            10,
            50,
            20,
            BLUE);

    if (isHurry) { DrawText("Hurry up !", 10, 70, 20, RED); }
}

void Game::action(Cameraman& camera, Vector2 mouse_pos) noexcept
{
    DestroyPool();
    CollisionPool();
    chrono_->updateTimer();

    for (auto& player : data_->players) player->Update();
    for (auto& entity : entities_) entity->Update();

    if (!camera.isMoving) camera.lookBetweenEntity(data_->players);

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
    }
    hurryUp();
}

void Game::DestroyPool() noexcept
{
    // suppression des entités désacivées
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
            if (hitbox == std::nullopt || other_hitbox == std::nullopt)
                continue;
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
            if (hitbox == std::nullopt || other_hitbox == std::nullopt)
                continue;
            if (!hitbox->get().getIsSolid()
                || !other_hitbox->get().getIsSolid())
                continue;
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
                entities_.emplace_back(NEW_WALL(vectorTemp));
            }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++)
            if (x % 2 != 0 && z % 2 != 0) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                entities_.emplace_back(NEW_WALL(vectorTemp));
            }

    // Génération des boites
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if ((x == -6 && z == -4) || (x == 6 && z == -4)
                || (x == -6 && z == 6) || (x == 6 && z == 6)
                || (x == -6 && z == -3) || (x == 6 && z == -3)
                || (x == -6 && z == 5) || (x == 6 && z == 5)
                || (x == -5 && z == -4) || (x == 5 && z == -4)
                || (x == -5 && z == 6) || (x == 5 && z == 6))
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
                entities_.emplace_back(
                    NEW_CRATE(vectorTemp, data_, &entities_));
        }
}

void Game::hurryUp(void) noexcept
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
        entities_.emplace_back(NEW_WALL(vectorTemp));
        lastTimeBlockPlace = chrono_->getTime();
        nbBlockPlaced++;
    }

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

Color Game::getBackgroundColor() const noexcept
{
    return (background_color_);
}