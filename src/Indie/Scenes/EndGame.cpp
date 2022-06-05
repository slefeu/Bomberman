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
    , background_color_(Colors::C_WHITE)
    , victory_music_(VICTORY_MUSIC)
{
}

EndGame::~EndGame() noexcept
{
    victory_music_.unload();
}

void EndGame::resetCameraman(Cameraman& camera) noexcept
{
    camera.tpTo({ 0.0f, 10.0f, 50.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 2.0f, 0.0f });
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void EndGame::display3D() noexcept
{
    for (auto& player : data_->players) { player->Display(); }
}

void EndGame::display2D() noexcept
{
    FpsHandler::draw(10, 10);
}

void EndGame::action([[maybe_unused]] Cameraman& camera, Vector2 mouse_pos) noexcept
{
    if (!isEnd) {
        int alive = 0;
        for (auto& player : data_->players)
            if (player->getEnabledValue()) alive++;
        if (alive == 0 || alive == 1) {
            for (auto& player : data_->players) {
                auto render    = player.get()->getComponent<Render>();
                auto transform = player.get()->getComponent<Transform3D>();

                if (!render.has_value() || !transform.has_value()) return;

                std::cout << "coucou" << std::endl;

                render->get().setAnimationId(3);
                transform->get().setPosition({ 0.0f, 0.0f, 0.5f });
                transform->get().setRotationAngle(90.0f);
            }
        }
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