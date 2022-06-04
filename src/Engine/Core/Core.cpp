/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#include "Core.hpp"

#include "Game.hpp"
#include "Home.hpp"

Core::Core(GameData* newData) noexcept
    : data(newData)
{
    createWindow();

    // Chargement des models 3D
    data->models.emplace_back(NEW_MODEL("assets/models/bomb.glb", "assets/textures/entities/bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.glb", "assets/textures/entities/wall.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/box.glb", "assets/textures/entities/box.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/items/i_roller.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/items/i_bomb.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/items/i_fire.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/item.glb", "assets/textures/items/item.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/fire.glb", "assets/textures/entities/fire.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/player.iqm", "assets/textures/player/white.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/player.iqm", "assets/textures/player/black.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/player.iqm", "assets/textures/player/blue.png"));
    data->models.emplace_back(NEW_MODEL("assets/models/player.iqm", "assets/textures/player/red.png"));

    data->models[(int)ModelType::M_PLAYER_1]->addAnimation("assets/models/player.iqm");
    data->models[(int)ModelType::M_PLAYER_2]->addAnimation("assets/models/player.iqm");
    data->models[(int)ModelType::M_PLAYER_3]->addAnimation("assets/models/player.iqm");
    data->models[(int)ModelType::M_PLAYER_4]->addAnimation("assets/models/player.iqm");

    // Chargement des sprites
    data->sprites.emplace_back(NEW_SPRITE_SCALE("assets/icones/white.png", 0, 0, 0.5f));
    data->sprites.emplace_back(NEW_SPRITE_SCALE("assets/icones/black.png", 0, 0, 0.5f));
    data->sprites.emplace_back(NEW_SPRITE_SCALE("assets/icones/blue.png", 0, 0, 0.5f));
    data->sprites.emplace_back(NEW_SPRITE_SCALE("assets/icones/red.png", 0, 0, 0.5f));

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
