/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Window
*/

#include "Window.hpp"

WindowManager::WindowManager(int width, int height, int fps) noexcept
    : width_(width)
    , height_(height)
    , fps_(fps)
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

    BeginDrawing();
    ClearBackground((Color){ color[0], color[1], color[2], 255 });
    scene.drawBackground();
    camera.begin3D();
    scene.display3D();
    EndMode3D();
    scene.display2D();
    EndDrawing();
}

bool WindowManager::isExit() noexcept
{
    return (WindowShouldClose());
}

int WindowManager::getWidth() const noexcept
{
    return (width_);
}

void WindowManager::resetHeight() noexcept
{
    height_ = GetScreenHeight();
}

void WindowManager::resetWidth() noexcept
{
    width_ = GetScreenWidth();
}

int WindowManager::getHeight() const noexcept
{
    return (height_);
}

float WindowManager::getFps() const noexcept
{
    return (fps_);
}

void WindowManager::setFps(float value) noexcept
{
    fps_ = value;
    FpsHandler::setFps(fps_);
}