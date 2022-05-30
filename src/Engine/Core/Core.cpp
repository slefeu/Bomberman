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

Core::Core(GameData* newData) noexcept
    : data(newData)
{
    // Create Window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(data->winWidth, data->winHeight, "indie Studio - Bomberman");
    SetTargetFPS(data->fps);

    // Chargement des models 3D
    data->models.emplace_back(NEW_MODEL("assets/models/bomb.obj", "assets/textures/bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.obj", "assets/textures/wall.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.obj", "assets/textures/box.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.obj", "assets/textures/i_roller.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.obj", "assets/textures/i_bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.obj", "assets/textures/i_fire.png"));

    // Génération des joueurs
    for (int i = 0; i != data->nbPlayer; i++) data->players.emplace_back(NEW_PLAYER(i, data));

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(data));
    scenes.emplace_back(std::make_unique<Game>(data));

    // Setting the first camera
    camera.position = SCENE->cameraPosition;
    camera.target   = SCENE->cameraTarget;
    camera.up       = SCENE->cameraUp;
}

void Core::switchScene(int scene) noexcept
{
    data->currentScene = scene;
    SCENE->resetCamera(camera);
}

void Core::run() noexcept
{
    while (!WindowShouldClose()) {
        // Events -------------------------------------------------------------
        // Va partir, c'est que pour les tests
        if (IsKeyPressed(KEY_LEFT)) switchScene((data->currentScene - 1) % scenes.size());
        if (IsKeyPressed(KEY_UP)) SCENE->resetCamera(camera);
        if (IsKeyPressed(KEY_DOWN)) camera.tpTo({ 0.0f, 0.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

        if (IsGamepadAvailable(0))
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) switchScene((data->currentScene - 1) % scenes.size());

        // Update -------------------------------------------------------------
        if (camera.isMoving) camera.isMoving = camera.smoothMove();
        SCENE->action(camera);

        // Display ------------------------------------------------------------
        BeginDrawing();
        ClearBackground(SCENE->backgroundColor);
        BeginMode3D(camera);
        SCENE->display3D();
        EndMode3D();
        SCENE->display2D();
        EndDrawing();
    }
}