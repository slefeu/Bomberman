/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Window
*/

#include "Window.hpp"

#include "raylib.h"

WindowManager::~WindowManager() noexcept
{
    CloseWindow();
}

void WindowManager::launch(int width, int height, int fps) const noexcept
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(width, height, "indie Studio - Bomberman");
    SetTargetFPS(fps);
    // ToggleFullscreen();
}

void WindowManager::display(Scene& scene, const Cameraman& camera) noexcept
{
    auto color = scene.getBackgroundColor().getColor();

    BeginDrawing();
    ClearBackground((Color){ color[0], color[1], color[2], 255 });
    scene.drawBackground();
    BeginMode3D(camera.getCamera());
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
    return (GetScreenWidth());
}

int WindowManager::getHeight() const noexcept
{
    return (GetScreenHeight());
}