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
    cameraPosition = { 0.0f, 12.0f, 12.0f };
    cameraTarget   = { 0.0f, 0.0f, 0.0f };
    cameraUp       = { 0.0f, 1.0f, 0.0f };

    _players.emplace_back(std::make_unique<Player>(1, GREEN));
    _players.emplace_back(std::make_unique<Player>(2, BLUE));
    _players.emplace_back(std::make_unique<Player>(3, PINK));
    _players.emplace_back(std::make_unique<Player>(4, YELLOW));

    _entities.emplace_back(std::make_unique<Box>((Vector3){ 0.0f, 0.0f, 0.0f }, 0.02f));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ -5.0f, 0.0f, -2.0f }, 0.01f));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ 2.0f, 0.0f, -4.0f }, 0.012f));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ -2.0f, 0.0f, -4.0f }, 0.012f));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ -4.0f, 0.0f, -2.0f }, 0.012f));
    _entities.emplace_back(std::make_unique<Box>((Vector3){ -4.0f, 0.0f, 2.0f }, 0.012f));
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
}

void Game::display2D() noexcept
{
    DrawText("Press LEFT to change scene", 10, 10, 20, BLACK);
    DrawText("Press UP to reset camera (mouvement lisse)", 10, 30, 20, BLACK);
    DrawText("Press DOWN to tp to (30, 30, 30) (mouvement brusque)", 10, 50, 20, BLACK);
    DrawFPS(700, 10);
    DrawText("Game", 10, 570, 20, GREEN);
}

void Game::action(Cameraman& camera) noexcept
{
    for (auto& player : _players) player->action(_entities);
    camera.lookBetweenEntities(_players);
}