/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

#include <iostream>

Home::Home(GameData* data, Core& core_ref) noexcept
    : Scene()
    , loop_music_(MENU_MUSIC)
    , core_entry_(core_ref)
    , data_(data)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH)
    , title_(TITLE_PATH, 30, 30)
{
    createButtons();
}

Home::~Home() noexcept
{
    loop_music_.unload();
    background_.unload();
    title_.unload();
    unloadButtons();
}

void Home::createButtons() noexcept
{
    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth / 2,
        data_->winHeight / 4,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(SceneType::GAME)); }),
        1,
        "assets/fonts/menu.ttf",
        "Play",
        data_->winWidth / 2 + 100,
        data_->winHeight / 4 + 45);

    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth / 2,
        (data_->winHeight / 4) + (150 * buttons_.size()),
        std::function<void(void)>([](void) { return; }),
        1,
        "assets/fonts/menu.ttf",
        "Load",
        data_->winWidth / 2 + 100,
        data_->winHeight / 4 + 150 * buttons_.size() + 45);

    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth / 2,
        data_->winHeight / 4 + (150 * buttons_.size()),
        std::function<void(void)>([this](void) { return (core_entry_.setExit(true)); }),
        1,
        "assets/fonts/menu.ttf",
        "Exit",
        data_->winWidth / 2 + 110,
        data_->winHeight / 4 + 150 * buttons_.size() + 45);
}

void Home::resetCameraman(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void Home::display3D() noexcept {}

void Home::display2D() noexcept
{
    FpsHandler::draw(10, 10);
    drawButtons();
}

void Home::action([[maybe_unused]] Cameraman& camera, MouseHandler mouse_) noexcept
{
    if (controller.isGamepadConnected(0)) {
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_UP))
            button_index_ = (button_index_ - 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_DOWN))
            button_index_ = (button_index_ + 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_B)) buttons_[button_index_].action();
        for (auto& it : buttons_) it.setState(0);
        buttons_[button_index_].setState(1);
    } else {
        for (auto& it : buttons_)
            if (it.checkCollision(mouse_pos)) { it.action(); }
    }
}

void Home::DestroyPool() noexcept {}

void Home::CollisionPool() noexcept {}

void Home::playMusic() noexcept
{
    loop_music_.play();
}

MusicManager Home::getMusicManager() const noexcept
{
    return (loop_music_);
}

Vector3 Home::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 Home::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 Home::getCameraUp() const noexcept
{
    return (camera_up_);
}

void Home::drawBackground() const noexcept
{
    background_.draw({ 255, 255, 255, 175 });
    title_.draw();
}

void Home::drawButtons() const noexcept
{
    for (auto it : buttons_) { it.draw(); }
}

void Home::unloadButtons() noexcept
{
    for (auto it : buttons_) { it.unload(); }
}

ColorManager Home::getBackgroundColor() const noexcept
{
    return (background_color_);
}