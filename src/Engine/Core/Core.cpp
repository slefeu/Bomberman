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
    : data_(newData)
    , window_(window)
{
    window_->launch(data_->winWidth, data_->winHeight, data_->fps);

    // Chargement des models 3D
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/bomb.glb", "assets/textures/entities/bomb.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/box.glb", "assets/textures/entities/wall.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/box.glb", "assets/textures/entities/box.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_roller.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_bomb.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/i_fire.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/item.glb", "assets/textures/items/item.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/fire.iqm", "assets/textures/entities/fire.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/white.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/black.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/blue.png"));
    data_->models.emplace_back(
        std::make_unique<Model3D>("assets/models/player.iqm", "assets/textures/player/red.png"));

    // Chargement des sprites
    data_->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/white.png", 0, 0, 0.5f));
    data_->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/black.png", 0, 0, 0.5f));
    data_->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/blue.png", 0, 0, 0.5f));
    data_->sprites.emplace_back(std::make_unique<Sprite>("assets/icones/red.png", 0, 0, 0.5f));

    if (scenes.size() != 0) scenes.clear();
    if (data_->players.size() != 0) data_->players.clear();

    // Loading all scenes
    scenes.emplace_back(std::make_unique<Home>(*this));
    scenes.emplace_back(std::make_unique<Game>(*this));
    scenes.emplace_back(std::make_unique<PlayerSelect>(*this));
    findScene().playMusic();
    switchScene(bomberman::SceneType::MENU);
}

Scene& Core::findScene() noexcept
{
    return (*scenes[static_cast<typename std::underlying_type<bomberman::SceneType>::type>(
        data_->getCurrentScene())]);
}

void Core::switchScene(const bomberman::SceneType& scene) noexcept
{
    data_->setCurrentScene(scene);
    findScene().playMusic();
    findScene().switchAction();
}

void Core::run() noexcept
{
    while (!exit_) {
        checkExit();
        if (camera.getIsMoving()) camera.setIsMoving(camera.smoothMove());
        audio_.update(findScene());
        data_->updateMouse();
        findScene().action();

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

WindowManager& Core::getWindow() noexcept
{
    return *window_;
}

Cameraman& Core::getCameraman() noexcept
{
    return camera;
}

GameData* Core::getData() const noexcept
{
    return (data_);
}
