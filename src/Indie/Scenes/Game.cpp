/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>

#include "Box.hpp"
#include "Crate.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Wall.hpp"
#include "raylib.h"

//-------------------------------------------------------------------------------------------------
// PUBLIC METHODS
//-------------------------------------------------------------------------------------------------

Game::Game(GameData* data) noexcept
    : Scene(data)
    , _chrono(std::make_unique<Timer>(data->timeParty))
    , isHurry(false)
    , nbBlockPlaced(0)
{
    cameraPosition  = { 0.0f, 11.0f, 1.0f };
    cameraTarget    = { 0.0f, 0.0f, 1.0f };
    cameraUp        = { 0.0f, 2.0f, 0.0f };
    backgroundColor = BLACK;

    // Assignation des bombes aux joueurs
    for (auto& player : data->players) {
        if (player->type != EntityType::E_PLAYER) continue;
        ((std::unique_ptr<Player>&)player)->setBombArray(&_entities);
    }

    createMap();
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Game::display3D() noexcept
{
    DrawPlane({ 0.0f, 0.0f, 1.0f }, { 13.0f, 11.0f }, { 0, 207, 68, 255 });
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if (z % 2 == 0 && x % 2 == 0) DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
            if (z % 2 != 0 && x % 2 != 0) DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
        }

    for (auto& player : PLAYERS) player->Display();
    for (auto& entity : _entities) entity->Display();
}

void Game::display2D() noexcept
{
    DrawFPS(10, 10);
    DrawText("Game", 10, 30, 20, GREEN);
    if (_chrono->timerDone()) DrawText("Party end", 10, 50, 20, BLUE);
    else
        DrawText(std::to_string(int(round(_chrono->getTime()))).data(), 10, 50, 20, BLUE);

    if (isHurry) { DrawText("Hurry up !", 10, 70, 20, RED); }
}

void Game::action(Cameraman& camera) noexcept
{
    DestroyPool();
    CollisionPool();
    _chrono->updateTimer();

    for (auto& player : PLAYERS) player->Update();
    for (auto& entity : _entities) entity->Update();

    if (!camera.isMoving) camera.lookBetweenGameObject3D(PLAYERS);

    // Modificatoin de nombre de joueur à l'écran
    if (IsKeyPressed(KEY_C) && data->nbPlayer < 4) {
        data->nbPlayer++;
        PLAYERS.emplace_back(std::make_unique<Player>(data->nbPlayer - 1, &_entities, data));
    }
    if (IsKeyPressed(KEY_V) && data->nbPlayer > 1) {
        data->nbPlayer--;
        PLAYERS.erase(PLAYERS.begin() + data->nbPlayer);
    }

    // Activation du Hurry Up !
    if (int(round(_chrono->getTime())) <= 55 && !isHurry) {
        isHurry            = true;
        lastTimeBlockPlace = _chrono->getTime();
    }
    if (nbBlockPlaced >= 80) isHurry = false;
    hurryUp();
}

void Game::DestroyPool() noexcept
{
    // suppression des entités désacivées
    size_t len = _entities.size();
    for (size_t i = 0; i != len; i++) {
        if (!_entities[i]->isEnable) {
            _entities.erase(_entities.begin() + i);
            len--;
            i--;
        }
    }
}

void Game::CollisionPool() noexcept
{
    // Collisions jouers/entités
    for (auto& player : PLAYERS) {
        for (auto& entity : _entities) {
            if (player->hitbox == nullptr || entity->hitbox == nullptr) continue;
            if (!player->hitbox->isSolid || !entity->hitbox->isSolid) continue;
            if (player->hitbox->isColliding(entity->hitbox)) {
                player->OnCollisionEnter(entity);
                entity->OnCollisionEnter(player);
            }
        }
    }
    // Collisions entités/entités
    for (auto& entity1 : _entities) {
        for (auto& entity : _entities) {
            if (entity1->hitbox == nullptr || entity->hitbox == nullptr) continue;
            if (!entity1->hitbox->isSolid || !entity->hitbox->isSolid) continue;
            if (entity1 == entity) continue;
            if (entity1->hitbox->isColliding(entity->hitbox)) {
                entity1->OnCollisionEnter(entity);
                entity->OnCollisionEnter(entity1);
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
// PRIVATE METHODS
//-------------------------------------------------------------------------------------------------

void Game::createMap(void) noexcept
{
    Vector3 vectorTemp;

    for (int i = 0; i < 100; i++) {
        int tempX = (rand() % 13) - 6.0f;
        int tempZ = (rand() % 12) - 5.0f;

        if ((int)tempX % 2 != 0 && (int)tempZ % 2 != 0) continue;

        if ((tempX == -6 && tempZ == -4) || (tempX == 6 && tempZ == -4) || (tempX == -6 && tempZ == 6) || (tempX == 6 && tempZ == 6)
            || (tempX == -6 && tempZ == -3) || (tempX == 6 && tempZ == -3) || (tempX == -6 && tempZ == 5) || (tempX == 6 && tempZ == 5)
            || (tempX == -5 && tempZ == -4) || (tempX == 5 && tempZ == -4) || (tempX == -5 && tempZ == 6) || (tempX == 5 && tempZ == 6))
            continue;

        vectorTemp = { tempX * 1.0f, 0.0f, tempZ * 1.0f };
        _entities.emplace_back(std::make_unique<Crate>(vectorTemp, MODELS(M_CRATE), data));
    }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++) {
            if (x % 2 != 0 && z % 2 != 0) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                _entities.emplace_back(std::make_unique<Wall>(vectorTemp, MODELS(M_WALL), data));
            }
        }

    // Ajout des murs autour de la carte
    for (int z = -5; z < 8; z++)
        for (int x = -7; x < 8; x++) {
            if (x == -7 || x == 7 || z == -5 || z == 7) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                _entities.emplace_back(std::make_unique<Wall>(vectorTemp, MODELS(M_WALL), data));
            }
        }
}

void Game::hurryUp(void) noexcept
{
    if (!isHurry) return;

    float time = _chrono->getTime();

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
        _entities.emplace_back(std::make_unique<Wall>(vectorTemp, MODELS(M_WALL), data));
        lastTimeBlockPlace = _chrono->getTime();
        nbBlockPlaced++;
    }
}