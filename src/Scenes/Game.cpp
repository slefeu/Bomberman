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

Game::Game(GameData* data) noexcept
    : Scene(data)
{
    cameraPosition = { 0.0f, 11.0f, 1.0f };
    cameraTarget   = { 0.0f, 0.0f, 1.0f };
    cameraUp       = { 0.0f, 2.0f, 0.0f };
    _chrono        = std::make_unique<Timer>(60);

    // Assignation des bombes aux joueurs
    for (auto& player : data->players) {
        if (player->type != EntityType::E_PLAYER) continue;
        std::unique_ptr<Player>& tempPlayer = (std::unique_ptr<Player>&)player;
        if (tempPlayer->bombs == nullptr) tempPlayer->bombs = &_bombs;
    }

    _items.emplace_back(std::make_unique<Item>((Vector3){ 0.0f, 0.0f, 0.0f }, MODELS(M_ITEM)));

    createMap();
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Game::display3D() noexcept
{
    DrawGrid(100, 1.0f);

    for (auto& player : PLAYERS) player->display();
    for (auto& entity : _entities) entity->display();
    for (auto& item : _items) item->display();

    size_t len = _bombs.size();
    for (size_t i = 0; i != len; i++) {
        if (_bombs[i]->update(_entities)) {
            _bombs.erase(_bombs.begin() + i);
            len--;
            i--;
        }
    }
}

void Game::display2D() noexcept
{
    DrawFPS(10, 10);
    DrawText("Game", 10, 30, 20, GREEN);
    if (_chrono->timerDone()) DrawText("Party end", 450, 300, 70, BLUE);
    else
        DrawText(std::to_string(int(round(_chrono->getTime()))).data(), 1200, 30, 50, BLUE);
}

void Game::action(Cameraman& camera) noexcept
{
    for (auto& player : PLAYERS) player->action(_entities);
    for (auto& item : _items) item->isColliding(PLAYERS);
    for (auto& bomb : _bombs) {
        bomb->isColliding(PLAYERS);
        bomb->isColliding(_entities);
        bomb->isColliding(_items);
    }
    if (!camera.isMoving) camera.lookBetweenGameObject3D(PLAYERS);

    // Modificatoin de nombre de joueur à l'écran
    if (IsKeyPressed(KEY_C) && data->nbPlayer < 4) {
        data->nbPlayer++;
        PLAYERS.emplace_back(std::make_unique<Player>(data->nbPlayer - 1, MAGENTA, &_bombs, MODELS(M_BOMB)));
    }
    if (IsKeyPressed(KEY_V) && data->nbPlayer > 1) {
        data->nbPlayer--;
        PLAYERS.erase(PLAYERS.begin() + data->nbPlayer);
    }
    _chrono->updateTimer();
}

void Game::createMap(void) noexcept
{
    // add 10 crates at random positions on the map
    for (int i = 0; i < 50; i++) {
        float tempX = (float)(rand() % 12) - 5.0f;
        float tempZ = (float)(rand() % 12) - 5.0f;

        if ((int)tempX % 2 != 0 && (int)tempZ % 2 != 0) continue;
        for (auto& player : PLAYERS)
            if (tempX == player->getPosition().x && tempZ == player->getPosition().z) continue;

        _entities.emplace_back(std::make_unique<Crate>((Vector3){ tempX, 0.0f, tempZ }, MODELS(M_CRATE)));
    }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++) {
            if (x % 2 != 0 && z % 2 != 0)
                _entities.emplace_back(std::make_unique<Wall>((Vector3){ x * 1.0f, 0.0f, z * 1.0f }, MODELS(M_WALL)));
        }

    // Ajout des murs autour de la carte
    for (int z = -5; z < 8; z++)
        for (int x = -7; x < 8; x++) {
            if (x == -7 || x == 7 || z == -5 || z == 7)
                _entities.emplace_back(std::make_unique<Wall>((Vector3){ x * 1.0f, 0.0f, z * 1.0f }, MODELS(M_WALL)));
        }
}
