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

Core::Core(Settings* settings) noexcept
{
    // Create Window
    InitWindow(settings->winWidth, settings->winHeight, "indie Studio - Bomberman");
    SetTargetFPS(settings->fps);

    // Chargement des models 3D
    _models.emplace_back(std::make_unique<Render3D>("Assets/Models/bomb.obj", "Assets/Textures/bomb.png"));
    _models.emplace_back(std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/wall.png"));
    _models.emplace_back(std::make_unique<Render3D>("Assets/Models/box.obj", "Assets/Textures/box.png"));

    // Génération des joueurs
    Color colors[4] = { PINK, BLUE, YELLOW, MAROON };
    for (int i = 0; i != settings->nbPlayer; i++)
        _players.emplace_back(std::make_unique<Player>(i, colors[i], nullptr, _models[0].get()));

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(settings));
    scenes.emplace_back(std::make_unique<Game>(&_players, &_models, settings));
    currentScene = 1;

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
        // Va partir, c'est que pour les tests
        if (IsKeyPressed(KEY_LEFT)) switchScene((currentScene - 1) % scenes.size());
        if (IsKeyPressed(KEY_UP)) SCENE->resetCamera(camera);
        if (IsKeyPressed(KEY_DOWN)) camera.tpTo({ 0.0f, 0.0f, 30.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });

        if (IsGamepadAvailable(0))
            if (IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN)) switchScene((currentScene - 1) % scenes.size());

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

    // Déchargement des éléments (necessaire pour les modèles 3D)
    for (auto& scene : scenes) scene.reset();
    for (auto& model : _models) model.reset();
    for (auto& player : _players) player.reset();

    CloseWindow();
}