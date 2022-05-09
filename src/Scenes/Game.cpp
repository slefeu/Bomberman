/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>

Game::Game() noexcept
{
    cameraPosition = {0.0f, 10.0f, 10.0f};
}

void Game::placeCamera(Cameraman& camera) noexcept
{
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};

    while (!camera.smoothMove(cameraPosition, 1)) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        display();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }
}

void Game::display() noexcept
{
    DrawSphere({0, 0, 0}, 2, RED);
    DrawGrid(10, 1.0f);
}

void Game::action() noexcept
{
    if (IsKeyPressed(KEY_UP))
        std::cout << "Game" << std::endl;
}