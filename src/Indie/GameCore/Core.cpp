/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#include "Core.hpp"

#include "Game.hpp"
#include "Home.hpp"
#include "PlayerSelect.hpp"

Core::Core() noexcept
    : data_(GameData())
    , window_(std::make_unique<WindowManager>(1920, 1040, 60))
{
    initGameModels();
    initSprites();
    initScenes();
}

Scene& Core::findScene() noexcept
{
    return (*scenes[static_cast<typename std::underlying_type<bomberman::SceneType>::type>(
        data_.getCurrentScene())]);
}

void Core::switchScene(const bomberman::SceneType& scene) noexcept
{
    data_.setCurrentScene(scene);
    findScene().playMusic();
    findScene().switchAction();
}

void Core::run() noexcept
{
    while (!exit_) {
        checkExit();
        checkCamera();
        AudioDevice::update(findScene());
        data_.updateMouse();
        findScene().action();
        window_->display(findScene(), camera_);
    }
}

void Core::checkCamera() noexcept
{
    if (camera_.getIsMoving()) camera_.setIsMoving(camera_.smoothMove());
}

void Core::checkExit() noexcept
{
    if (window_->isExit()) { setExit(true); }
}

void Core::setExit(bool value) noexcept
{
    exit_ = value;
}

WindowManager& Core::getWindow() noexcept
{
    return (*window_);
}

Cameraman& Core::getCameraman() noexcept
{
    return (camera_);
}

GameData& Core::getData() noexcept
{
    return (data_);
}

const GameData& Core::getData() const noexcept
{
    return (data_);
}

void Core::initGameModels() noexcept
{
    data_.addModel("assets/models/bomb.glb", "assets/textures/entities/bomb.png");
    data_.addModel("assets/models/box.glb", "assets/textures/entities/wall.png");
    data_.addModel("assets/models/box.glb", "assets/textures/entities/box.png");
    data_.addModel("assets/models/item.glb", "assets/textures/items/i_roller.png");
    data_.addModel("assets/models/item.glb", "assets/textures/items/i_bomb.png");
    data_.addModel("assets/models/item.glb", "assets/textures/items/i_fire.png");
    data_.addModel("assets/models/item.glb", "assets/textures/items/item.png");
    data_.addModel("assets/models/fire.iqm", "assets/textures/entities/fire.png");
    data_.addModel("assets/models/player.iqm", "assets/textures/player/white.png");
    data_.addModel("assets/models/player.iqm", "assets/textures/player/black.png");
    data_.addModel("assets/models/player.iqm", "assets/textures/player/blue.png");
    data_.addModel("assets/models/player.iqm", "assets/textures/player/red.png");
}

void Core::initSprites() noexcept
{
    data_.addSprite("assets/icones/white.png");
    data_.addSprite("assets/icones/black.png");
    data_.addSprite("assets/icones/blue.png");
    data_.addSprite("assets/icones/red.png");
}

void Core::initScenes() noexcept
{
    scenes.emplace_back(std::make_unique<Home>(*this));
    scenes.emplace_back(std::make_unique<Game>(*this));
    scenes.emplace_back(std::make_unique<PlayerSelect>(*this));
    findScene().playMusic();
    switchScene(bomberman::SceneType::MENU);
}