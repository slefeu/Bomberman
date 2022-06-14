/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Plane.cpp
*/

#include "Plane.hpp"

#include "raylib.h"

void Plane::draw(Vector3D pos, Vector2D size, std::array<unsigned char, 3> color) noexcept
{
    Vector3 tempPos  = { pos.x, pos.y, pos.z };
    Vector2 tempSize = { size.x, size.y };
    Color   col      = { color[0], color[1], color[2], 255 };

    DrawPlane(tempPos, tempSize, col);
}