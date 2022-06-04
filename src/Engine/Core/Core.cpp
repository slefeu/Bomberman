/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#include "Core.hpp"

#include <type_traits>

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
    data->models.emplace_back(
        NEW_MODEL("assets/models/bomb.obj", "assets/textures/bomb.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/box.obj", "assets/textures/wall.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/box.obj", "assets/textures/box.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/item.obj", "assets/textures/i_roller.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/item.obj", "assets/textures/i_bomb.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/item.obj", "assets/textures/i_fire.png"));
    data->models.emplace_back(
        NEW_MODEL("assets/models/item.obj", "assets/textures/item.png"));

    // Génération des joueurs
    for (int i = 0; i != data->nbPlayer; i++)
        data->players.emplace_back(std::make_unique<Player>(i, data));

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(data, *this));
    scenes.emplace_back(std::make_unique<Game>(data, *this));
    findScene().playMusic();

    // Setting the first camera
    camera.position = findScene().getCameraPosition();
    camera.target   = findScene().getCameraTarget();
    camera.up       = findScene().getCameraUp();
}

Scene& Core::findScene() noexcept
{
    return (*scenes[static_cast<typename std::underlying_type<SceneType>::type>(
        data->getCurrentScene())]);
}

void Core::switchScene(const SceneType& scene) noexcept
{
    data->setCurrentScene(scene);
    findScene().resetCamera(camera);
    findScene().playMusic();
}

void Core::run() noexcept
{
    while (!exit_) {
        // Update -------------------------------------------------------------
        checkExit();
        if (camera.isMoving) camera.isMoving = camera.smoothMove();
        audio_.update(findScene());
        data->updateMouse();
        findScene().action(camera, data->getMousePosition());

        // Display ------------------------------------------------------------
        BeginDrawing();
        ClearBackground(findScene().getBackgroundColor());
        findScene().drawBackground();
        BeginMode3D(camera);
        findScene().display3D();
        EndMode3D();
        findScene().display2D();
        EndDrawing();
    }
}

void Core::checkExit() noexcept
{
    if (WindowShouldClose()) exit_ = true;
}

void Core::setExit(bool value) noexcept
{
    exit_ = value;
}