/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#include "Core.hpp"

#include <iostream>

#include "Game.hpp"
#include "Home.hpp"
#include "Vector3Tools.hpp"

Core::Core(int height, int width) noexcept
{
    InitWindow(height, width, "indie Studio - Bomberman");
    currentScene = 0;

    scenes.emplace_back(std::make_unique<Home>());
    scenes.emplace_back(std::make_unique<Game>());

    // scenes[currentScene]->placeCamera(camera);
    camera.position = scenes[currentScene]->cameraPosition;
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
}

void Core::setFPS(int fps) noexcept
{
    SetTargetFPS(fps);
}

void Core::switchScene(int scene) noexcept
{
    std::cout << "Switching to scene " << scene << std::endl;
    currentScene = scene;
    scenes[currentScene]->placeCamera(camera);
}

void Core::run() noexcept
{
    while (!WindowShouldClose()) {
        // Update -------------------------------------------------------------
        if (IsKeyPressed(KEY_LEFT))
            switchScene((currentScene - 1) % scenes.size());
        if (camera.isMoving)
            camera.isMoving = camera.smoothMove(camera.target, 1);
        scenes[currentScene]->action();

        // Display ------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        scenes[currentScene]->display();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }
    CloseWindow();
}