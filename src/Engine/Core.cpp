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
    InitWindow(data->winWidth, data->winHeight, "indie Studio - Bomberman");
    SetTargetFPS(data->fps);

    // Chargement des models 3D
    data->models.emplace_back(std::make_unique<Render3D>("Assets/Models/bomb.obj", "Assets/Textures/bomb.png"));
    data->models.emplace_back(std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/wall.png"));
    data->models.emplace_back(std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/box.png"));

    // Génération des joueurs
    Color colors[4] = { PINK, BLUE, YELLOW, MAROON };
    for (int i = 0; i != data->nbPlayer; i++)
        data->players.emplace_back(std::make_unique<Player>(i, colors[i], nullptr, MODELS(M_BOMB)));

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
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        SCENE->display3D();
        EndMode3D();
        SCENE->display2D();
        EndDrawing();
    }
}