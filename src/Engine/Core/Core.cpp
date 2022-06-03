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
    createWindow();

    // Chargement des models 3D
    data->models.emplace_back(NEW_MODEL("assets/models/bomb.glb", "assets/textures/bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.glb", "assets/textures/wall.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.glb", "assets/textures/box.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/i_roller.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/i_bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/i_fire.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/item.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/fire.glb", "assets/textures/fire.png"));

    data->sprites.emplace_back(NEW_SPRITE("assets/icones/white.png"));
    data->sprites.emplace_back(NEW_SPRITE("assets/icones/red.png"));
    data->sprites.emplace_back(NEW_SPRITE("assets/icones/blue.png"));
    data->sprites.emplace_back(NEW_SPRITE("assets/icones/black.png"));

    resetData();
    camera.tpTo(SCENE->cameraPosition, SCENE->cameraTarget, SCENE->cameraUp);
}

void Core::createWindow() noexcept
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(data->winWidth, data->winHeight, "indie Studio - Bomberman");
    SetTargetFPS(data->fps);
}

void Core::resetData() noexcept
{
    if (scenes.size() != 0) scenes.clear();
    if (data->players.size() != 0) data->players.clear();

    // Génération des joueurs
    for (int i = 0; i != data->nbPlayer; i++) data->players.emplace_back(NEW_PLAYER(i, data));

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(data));
    scenes.emplace_back(std::make_unique<Game>(data));
}

void Core::switchScene(const int& scene) noexcept
{
    data->currentScene = scene;
    SCENE->resetCameraman(camera);
}

void Core::run() noexcept
{
    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_SPACE)) resetData();

        if (camera.getIsMoving()) camera.setIsMoving(camera.smoothMove());
        SCENE->action(camera);

        // Display ------------------------------------------------------------
        BeginDrawing();
        ClearBackground(SCENE->backgroundColor);
        BeginMode3D(camera.getCamera());
        SCENE->display3D();
        EndMode3D();
        SCENE->display2D();
        EndDrawing();
    }
}
