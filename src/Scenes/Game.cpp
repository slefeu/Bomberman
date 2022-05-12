/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>

#include "Box.hpp"
#include "Player.hpp"

Game::Game() noexcept
{
    cameraPosition = { 0.0f, 11.0f, 1.0f };
    cameraTarget   = { 0.0f, 0.0f, 0.0f };
    cameraUp       = { 0.0f, 2.0f, 0.0f };

    _players.emplace_back(std::make_unique<Player>(0, PINK, &_bombs));
    _players.emplace_back(std::make_unique<Player>(1, BLUE, &_bombs));
    _players.emplace_back(std::make_unique<Player>(2, YELLOW, &_bombs));
    _players.emplace_back(std::make_unique<Player>(3, MAROON, &_bombs));

    _entities.emplace_back(std::make_unique<Box>((Vector3){ -5.0f, 0.0f, 0.0f }, Vector3{ 0.5f, 0.5f, 10.5f }));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ 5.0f, 0.0f, 0.0f }, Vector3{ 0.5f, 0.5f, 10.5f }));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ 0.0f, 0.0f, -5.0f }, Vector3{ 10.5f, 0.5f, 0.5f }));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ 0.0f, 0.0f, 5.0f }, Vector3{ 10.5f, 0.5f, 0.5f }));
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Game::display3D() noexcept
{
    DrawGrid(100, 1.0f);

    for (auto& player : _players) player->display();
    for (auto& entity : _entities) entity->display();

    size_t len = _bombs.size();
    for (size_t i = 0; i != len; i++) {
        if (_bombs[i]->update()) {
            _bombs[i].release();
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
    if (!camera.isMoving) camera.lookBetweenEntities(_players);
}