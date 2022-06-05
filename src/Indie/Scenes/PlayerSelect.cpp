/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** PlayerSelect
*/

#include "PlayerSelect.hpp"

PlayerSelect::PlayerSelect(GameData* data, Core& core_ref) noexcept
    : Scene()
    , loop_music_(MUSIC)
    , core_entry_(core_ref)
    , data_(data)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH, 0, 0, 1.1)
    , title_(TITLE_PATH, 30, 30)

{
}

PlayerSelect::~PlayerSelect() noexcept
{
    loop_music_.unload();
    background_.unload();
    title_.unload();
}

void PlayerSelect::resetCameraman(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void PlayerSelect::display3D() noexcept {}

void PlayerSelect::display2D() noexcept
{
    FpsHandler::draw(10, 10);
}

void PlayerSelect::action([[maybe_unused]] Cameraman& camera, MouseHandler mouse_) noexcept {}

void PlayerSelect::DestroyPool() noexcept {}

void PlayerSelect::CollisionPool() noexcept {}

void PlayerSelect::playMusic() const noexcept
{
    loop_music_.play();
}

MusicManager PlayerSelect::getMusicManager() const noexcept
{
    return (loop_music_);
}

Vector3 PlayerSelect::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 PlayerSelect::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 PlayerSelect::getCameraUp() const noexcept
{
    return (camera_up_);
}

void PlayerSelect::drawBackground() const noexcept
{
    background_.draw({ 255, 255, 255, 175 });
    title_.draw();
}

ColorManager PlayerSelect::getBackgroundColor() const noexcept
{
    return (background_color_);
}