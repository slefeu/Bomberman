/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

Home::Home(GameData* data) noexcept
    : Scene(data)
{
    cameraPosition  = { 0.0f, 11.0f, 20.0f };
    cameraTarget    = { 0.0f, 0.0f, 0.0f };
    cameraUp        = { 0.0f, 2.0f, 0.0f };
    backgroundColor = RAYWHITE;
}

void Home::resetCameraman(Cameraman& camera) noexcept
{
    camera.moveTo(cameraPosition, cameraTarget, cameraUp);
}

void Home::display3D() noexcept
{
    DrawCube({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, BLUE);
    DrawCubeWires({ 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
    DrawGrid(100, 1.0f);
}

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