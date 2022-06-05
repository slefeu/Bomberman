/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** EndGame
*/

#include "EndGame.hpp"

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
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void EndGame::display3D() noexcept {}

void EndGame::display2D() noexcept
{
    FpsHandler::draw(10, 10);
}

void EndGame::action([[maybe_unused]] Cameraman& camera, Vector2 mouse_pos) noexcept {}

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