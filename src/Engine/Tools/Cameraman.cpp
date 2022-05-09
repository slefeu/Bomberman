/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#include "Cameraman.hpp"

#include <math.h>

#include <iostream>

#include "Vector3Tools.hpp"

Cameraman::Cameraman() noexcept
{
    fovy = 60.0f;
    projection = CAMERA_PERSPECTIVE;
}

void Cameraman::moveX(float x) noexcept
{
    position.x += x;
}

void Cameraman::moveY(float y) noexcept
{
    position.y += y;
}

void Cameraman::moveZ(float z) noexcept
{
    position.z += z;
}

bool Cameraman::smoothMove(Vector3 to, float speed) noexcept
{
    Vector3 pos = to;
    Vector3 dir;
    dir.x = (position.x < pos.x) ? 1.0f : -1.0f;
    dir.y = (position.y < pos.y) ? 1.0f : -1.0f;
    dir.z = (position.z < pos.z) ? 1.0f : -1.0f;

    if (position.x != pos.x || position.y != pos.y || position.z != pos.z) {
        if (pos.x != position.x)
            moveX(dir.x * speed);
        if (pos.y != position.y)
            moveY(dir.y * speed);
        if (pos.z != position.z)
            moveZ(dir.z * speed);
        return false;
    }
    return true;
}