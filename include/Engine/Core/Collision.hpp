/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Collision
*/

#pragma once

#include "raylib.h"

class Collision
{
  public:
    Collision() noexcept  = default;
    ~Collision() noexcept = default;
    bool isColliding(
        const Vector3& pos, const Vector3& size, const Vector3& otherPos, const Vector3& otherSize) noexcept;
};
