/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>

#include "Player.hpp"

Game::Game() noexcept
{
    cameraPosition = { 0.0f, 10.0f, 10.0f };
    cameraTarget   = { 0.0f, 0.0f, 0.0f };
    cameraUp       = { 0.0f, 1.0f, 0.0f };

    // _entities.emplace_back(std::make_unique<Player>());
    _players.emplace_back(std::make_unique<Player>(1));
    _players.emplace_back(std::make_unique<Player>(2, BLUE));
}

void Game::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Game::display3D() noexcept
{
    DrawSphere({ 0, 0, 0 }, 2, RED);
    DrawGrid(10, 1.0f);

    for (auto& entity : _entities) entity->display();
    for (auto& player : _players) player->display();
}

void Game::display2D() noexcept
{
    DrawText("Press LEFT to change scene", 10, 10, 20, BLACK);
    DrawText("Press UP to reset camera (mouvement lisse)", 10, 30, 20, BLACK);
    DrawText("Press DOWN to tp to (30, 30, 30) (mouvement brusque)", 10, 50, 20, BLACK);
    DrawFPS(700, 10);
    DrawText("Game", 10, 570, 20, GREEN);
}

void Game::action() noexcept
{
    for (auto& player : _players) player->action();
}