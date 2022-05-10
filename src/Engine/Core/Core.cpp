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

#define SCENE scenes[currentScene]

Core::Core(int height, int width, int fps) noexcept
{
    // Create Window
    InitWindow(height, width, "indie Studio - Bomberman");
    SetTargetFPS(fps);

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>());
    scenes.emplace_back(std::make_unique<Game>());
    currentScene = 0;

    // Setting the first camera
    camera.position = SCENE->cameraPosition;
    camera.target   = SCENE->cameraTarget;
    camera.up       = SCENE->cameraUp;
}

void Core::switchScene(int scene) noexcept
{
    currentScene = scene;
    SCENE->resetCamera(camera);
}

void Core::run() noexcept
{
    while (!WindowShouldClose()) {
        // Events -------------------------------------------------------------
        if (IsKeyPressed(KEY_LEFT)) switchScene((currentScene - 1) % scenes.size());
        if (IsKeyPressed(KEY_UP)) SCENE->resetCamera(camera);
        if (IsKeyPressed(KEY_DOWN)) camera.tpTo({ 30.0f, 30.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

        // Update -------------------------------------------------------------
        if (camera.isMoving) camera.isMoving = camera.smoothMove();
        SCENE->action(camera);

        // Display ------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        SCENE->display3D();
        EndMode3D();
        SCENE->display2D();
        EndDrawing();
    }
    CloseWindow();
}