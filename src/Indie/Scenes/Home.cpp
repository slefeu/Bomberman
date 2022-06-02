/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

#include "Shortcuts.hpp"

Home::Home(GameData* data) noexcept
    : Scene(data)
{
    loop_music_ = LoadMusicStream(MENU_MUSIC);

    // Sound sound = LoadSound("Assets/Audios/Menu.wav");
    // sounds.push_back(std::make_unique<Sound>(sound));
}

Home::~Home() noexcept
{
    UnloadMusicStream(loop_music_);
}

void Home::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void Home::display3D() noexcept {}

void Home::display2D() noexcept
{
    DrawFPS(10, 10);
    DrawText("Home", 10, 30, 20, GREEN);
}

void Home::action(Cameraman& camera) noexcept
{
    (void)camera;
}

void Home::DestroyPool() noexcept {}

void Home::CollisionPool() noexcept {}

Music Home::getLoopMusic() const noexcept
{
    return (loop_music_);
}

void Home::playMusic() const noexcept
{
    PlayMusicStream(loop_music_);
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

Color Home::getBackgroundColor() const noexcept
{
    return (background_color_);
}
