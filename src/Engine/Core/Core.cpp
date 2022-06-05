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
#include "PlayerSelect.hpp"

Core::Core(GameData* newData, WindowManager* window) noexcept
    : data(newData)
    , window_(window)
{
    window_->launch(data->winWidth, data->winHeight, data->fps);

    // Chargement des models 3D
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/bomb.glb", "assets/textures/entities/bomb.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/box.glb", "assets/textures/entities/wall.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/box.glb", "assets/textures/entities/box.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_roller.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_bomb.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_fire.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/item.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/fire.iqm", "assets/textures/entities/fire.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/white.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/black.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/blue.png"));
    data->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/red.png"));

    // Chargement des sprites
    data->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/white.png", 0, 0, 0.5f));
    data->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/black.png", 0, 0, 0.5f));
    data->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/blue.png", 0, 0, 0.5f));
    data->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/red.png", 0, 0, 0.5f));

    resetData();
    camera.tpTo(
        findScene().getCameraPosition(), findScene().getCameraTarget(), findScene().getCameraUp());
}

void Core::resetData() noexcept
{
    if (scenes.size() != 0) scenes.clear();
    if (data->players.size() != 0) data->players.clear();

    // Génération des joueurs
    for (int i = 0; i != data->nbPlayer; i++)
        data->players.emplace_back(std::make_unique<Player>(i, data));

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(data, *this));
    scenes.emplace_back(std::make_unique<Game>(data, *this));
    scenes.emplace_back(std::make_unique<PlayerSelect>(data, *this));
    findScene().playMusic();
}

Scene& Core::findScene() noexcept
{
    return (*scenes[static_cast<typename std::underlying_type<SceneType>::type>(
        data->getCurrentScene())]);
}

void Core::switchScene(const SceneType& scene) noexcept
{
    data->setCurrentScene(scene);
    findScene().resetCameraman(camera);
    findScene().playMusic();
}

void Core::run() noexcept
{
    while (!exit_) {
        // Update -------------------------------------------------------------
        checkExit();
        if (camera.getIsMoving()) camera.setIsMoving(camera.smoothMove());
        audio_.update(findScene());
        data->updateMouse();
        findScene().action(camera, data->getMouseHandler());

        // Display ------------------------------------------------------------
        window_->display(findScene(), camera);
    }
}

void Core::checkExit() noexcept
{
    if (window_->isExit()) { exit_ = true; }
}

void Core::setExit(bool value) noexcept
{
    exit_ = value;
}