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
    cameraPosition = {20.0f, 50.0f, 20.0f};
}

void Home::placeCamera(Cameraman& camera) noexcept
{
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};

    while (!camera.smoothMove(cameraPosition, 1)) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);
        display();
        EndMode3D();
        DrawFPS(10, 10);
        EndDrawing();
    }
}

void Home::display() noexcept
{
    DrawCube({0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, BLUE);
    DrawCubeWires({0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, RED);
    DrawGrid(10, 1.0f);
}

void Home::action() noexcept
{
    if (IsKeyPressed(KEY_UP))
        std::cout << "Home" << std::endl;
}
