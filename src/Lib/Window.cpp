/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Window
*/

#include "Window.hpp"

WindowManager::WindowManager(int width, int height, int fps) noexcept
    : AWindow(width, height, fps)
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width_, height_, "Indie Studio - Bomberman");
    AudioDevice::initialize();
    FpsHandler::setFps(fps_);
}

WindowManager::~WindowManager() noexcept
{
    AudioDevice::close();
    CloseWindow();
}

void WindowManager::display(Scene& scene, const Cameraman& camera) noexcept
{
    auto color = scene.getBackgroundColor().getColor();
    Color col   = { color[0], color[1], color[2], 255 };

    BeginDrawing();
    ClearBackground(col);
    scene.SystemDisplay();
    EndDrawing();
}

bool WindowManager::isExit() noexcept
{
    return (WindowShouldClose());
}

void WindowManager::resetHeight() noexcept
{
    height_ = GetScreenHeight();
}

void WindowManager::resetWidth() noexcept
{
    width_ = GetScreenWidth();
}

void WindowManager::setFps(float value) noexcept
{
    fps_ = value;
    FpsHandler::setFps(fps_);
}

void WindowManager::decreaseFps() noexcept
{
    if (fps_ == 30) return;
    index_--;
    fps_ = possible_fps_[index_];
    FpsHandler::setFps(fps_);
}

void WindowManager::increaseFps() noexcept
{
    if (fps_ == 120) return;
    index_++;
    fps_ = possible_fps_[index_];
    FpsHandler::setFps(fps_);
}

void WindowManager::increaseMusic() noexcept
{
    if (music_percent_ == 100) return;
    music_percent_ = music_percent_ + 10;
    AudioDevice::setMusic(music_percent_);
}

void WindowManager::decreaseMusic() noexcept
{
    if (music_percent_ == 0) return;
    music_percent_ = music_percent_ - 10;
    AudioDevice::setMusic(music_percent_);
}

int WindowManager::getMusicPercentage() const noexcept
{
    return (music_percent_);
}