/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#include "Core.hpp"

#include "Game.hpp"
#include "Home.hpp"
#include "Load.hpp"
#include "PlayerSelect.hpp"
#include "Splash.hpp"

Core::Core() noexcept
    : window_(std::make_unique<WindowManager>(1920, 1040, 60))
{
    initGameModels();
    initSprites();
    initScenes();
}

Core::~Core() noexcept
{
    data_.unloadAll();
    for (auto& scene : scenes) { scene.reset(); }
    window_.reset();
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
        displayScene();
    }
}

void Core::displayScene() noexcept
{
    window_->display(findScene(), camera_);
}

void Core::checkCamera() noexcept
{
    if (camera_.getIsMoving()) camera_.setIsMoving(camera_.smoothMove());
}

void Core::checkExit() noexcept
{
    if (window_->isExit()) { setExit(true); }
}

WindowManager& Core::getWindow() noexcept
{
    return (*window_);
}

MyCameraman& Core::getCameraman() noexcept
{
    return (camera_);
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
    data_.addSprite("assets/textures/home/splash.png", 1);
    data_.addSprite("assets/icones/white.png", 0.5f);
    data_.addSprite("assets/icones/black.png", 0.5f);
    data_.addSprite("assets/icones/blue.png", 0.5f);
    data_.addSprite("assets/icones/red.png", 0.5f);
}

void Core::initScenes() noexcept
{
    scenes.emplace_back(std::make_unique<Home>(*this));
    scenes.emplace_back(std::make_unique<Game>(*this));
    scenes.emplace_back(std::make_unique<PlayerSelect>(*this));
    scenes.emplace_back(std::make_unique<Splash>(*this));
    scenes.emplace_back(std::make_unique<Load>(*this));
    findScene().playMusic();
    switchScene(bomberman::SceneType::SPLASH);
}