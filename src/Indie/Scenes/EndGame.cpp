/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** EndGame
*/

#include "EndGame.hpp"

#include <iostream>

#include "Error.hpp"

EndGame::EndGame(GameData* data, Core& core_ref) noexcept
    : Scene()
    , core_entry_(core_ref)
    , data_(data)
    , background_color_(Colors::C_BLACK)
    , victory_music_(VICTORY_MUSIC)
{
    createButtons();
}

EndGame::~EndGame() noexcept
{
    victory_music_.unload();
    unloadButtons();
}

void EndGame::resetCameraman(Cameraman& camera) noexcept
{
    camera.tpTo({ 0.0f, 10.0f, 30.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 2.0f, 0.0f });
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void EndGame::switchAction() noexcept
{
    int alive = 0;
    for (auto& player : data_->players)
        if (player->getEnabledValue()) alive++;
    if (alive == 0 || alive == 1) {
        for (auto& player : data_->players) {
            auto render    = player.get()->getComponent<Render>();
            auto transform = player.get()->getComponent<Transform3D>();

            if (!render.has_value() || !transform.has_value()) return;
            render->get().setSkipFrame(1);
            render->get().setAnimationId(3);
            transform->get().setPosition({ 0.0f, 0.0f, 0.5f });
            transform->get().setRotationAngle(90.0f);
        }
    }
}

void EndGame::display3D() noexcept
{
    float nbPlayers = 0;
    for (auto& player : data_->players) {
        if (!player->getEnabledValue()) continue;

        auto render    = player->getComponent<Render>();
        auto transform = player->getComponent<Transform3D>();

        if (!render.has_value() || !transform.has_value()) continue;

        Vector3 position = { 0, 0, 0 };
        Vector3 rotation = { 0, 1, 0 };

        render->get().setSkipFrame(1);
        render->get().setAnimationId(3);
        render->get().displayModelV(transform->get(), position, rotation, 90.0f);
        nbPlayers++;
    }
}

void EndGame::display2D() noexcept
{
    FpsHandler::draw(10, 10);
    drawButtons();
}

void EndGame::createButtons() noexcept
{
    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth / 2,
        data_->winHeight / 4,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(SceneType::GAME)); }),
        1,
        "assets/fonts/menu.ttf",
        "Restart",
        data_->winWidth / 2 + 100,
        data_->winHeight / 4 + 45);

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

void EndGame::action([[maybe_unused]] Cameraman& camera, MouseHandler mouse_pos) noexcept
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

void EndGame::DestroyPool() noexcept {}

void EndGame::CollisionPool() noexcept {}

void EndGame::playMusic() noexcept
{
    victory_music_.play();
}

MusicManager EndGame::getMusicManager() const noexcept
{
    return (victory_music_);
}

Vector3 EndGame::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 EndGame::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 EndGame::getCameraUp() const noexcept
{
    return (camera_up_);
}

ColorManager EndGame::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void EndGame::drawButtons() const noexcept
{
    for (auto it : buttons_) { it.draw(); }
}

void EndGame::unloadButtons() noexcept
{
    for (auto it : buttons_) { it.unload(); }
}