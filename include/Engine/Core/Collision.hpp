/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Collision
*/

#ifndef COLLISION_HPP_
#define COLLISION_HPP_

#include "raylib.h"

class Collision
{
  public:
    Collision() noexcept  = default;
    ~Collision() noexcept = default;
    bool isColliding(Vector3 pos, Vector3 size, Vector3 otherPos, Vector3 otherSize) noexcept;
};

#endif /* !COLLISION_HPP_ */
