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
#include "Player.hpp"
#include "Wall.hpp"

Game::Game() noexcept
{
    cameraPosition = { 0.0f, 11.0f, 1.0f };
    cameraTarget   = { 0.0f, 0.0f, 1.0f };
    cameraUp       = { 0.0f, 2.0f, 0.0f };

    modelBomb  = std::make_unique<Render3D>("Assets/Models/bomb.obj", "Assets/Textures/bomb.png");
    modelWall  = std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/wall.png");
    modelCrate = std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/box.png");

    _players.emplace_back(std::make_unique<Player>(0, PINK, &_bombs, &modelBomb));
    _players.emplace_back(std::make_unique<Player>(1, BLUE, &_bombs, &modelBomb));
    _players.emplace_back(std::make_unique<Player>(2, YELLOW, &_bombs, &modelBomb));
    _players.emplace_back(std::make_unique<Player>(3, MAROON, &_bombs, &modelBomb));

    // add 10 crates at random positions on the map
    for (int i = 0; i < 50; i++) {
        float tempX = (float)(rand() % 12) - 5.0f;
        float tempZ = (float)(rand() % 12) - 5.0f;

        if ((int)tempX % 2 != 0 && (int)tempZ % 2 != 0) continue;
        if (tempX == _players[0]->getPosition().x && tempZ == _players[0]->getPosition().z) continue;
        if (tempX == _players[1]->getPosition().x && tempZ == _players[1]->getPosition().z) continue;
        if (tempX == _players[2]->getPosition().x && tempZ == _players[2]->getPosition().z) continue;
        if (tempX == _players[3]->getPosition().x && tempZ == _players[3]->getPosition().z) continue;

        _entities.emplace_back(std::make_unique<Crate>((Vector3){ tempX, 0.0f, tempZ }, &modelCrate));
    }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++) {
            if (x % 2 != 0 && z % 2 != 0)
                _entities.emplace_back(std::make_unique<Wall>((Vector3){ x * 1.0f, 0.0f, z * 1.0f }, &modelWall));
        }

    // Ajout des murs autour de la carte
    for (int z = -5; z < 8; z++)
        for (int x = -7; x < 8; x++) {
            if (x == -7 || x == 7 || z == -5 || z == 7)
                _entities.emplace_back(std::make_unique<Wall>((Vector3){ x * 1.0f, 0.0f, z * 1.0f }, &modelWall));
        }
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Game::display3D() noexcept
{
    DrawGrid(100, 1.0f);
    // DrawPlane({ 0.0f, 0.0f, 0.0f }, { 100.0f, 100.0f }, DARKGREEN);

    for (auto& player : _players) player->display();
    for (auto& entity : _entities) entity->display();

    size_t len = _bombs.size();
    for (size_t i = 0; i != len; i++) {
        if (_bombs[i]->update()) {
            _bombs[i].reset();
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
}

void Game::action(Cameraman& camera) noexcept
{
    for (auto& player : _players) player->action(_entities);
    for (auto& bomb : _bombs) {
        bomb->isColliding(_players);
        bomb->isColliding(_entities);
    }
    if (!camera.isMoving) camera.lookBetweenGameObject3D(_players);
}