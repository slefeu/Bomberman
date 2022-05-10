/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

#include <iostream>

Home::Home() noexcept
{
    cameraPosition = { 20.0f, 50.0f, 20.0f };
    cameraTarget   = { 0.0f, 0.0f, 0.0f };
    cameraUp       = { 0.0f, 1.0f, 0.0f };
}

void Home::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Home::display3D() noexcept
{
    DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLUE);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
    DrawGrid(10, 1.0f);
}

void Home::display2D() noexcept
{
    DrawText("Press LEFT to change scene", 10, 10, 20, BLACK);
    DrawText("Press UP to reset camera (mouvement lisse)", 10, 30, 20, BLACK);
    DrawText("Press DOWN to tp to (30, 30, 30) (mouvement brusque)", 10, 50, 20, BLACK);
    DrawFPS(700, 10);
    DrawText("Home", 10, 570, 20, GREEN);
}

void Home::action() noexcept
{
    if (IsKeyPressed(KEY_RIGHT)) std::cout << "Home" << std::endl;
}
