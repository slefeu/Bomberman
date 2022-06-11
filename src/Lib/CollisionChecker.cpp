/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** CollisionChecker
*/

#include "CollisionChecker.hpp"

#include "raylib.h"

bool CollisionChecker::check(const Vector3D& pos,
    const Vector3D&                          size,
    const Vector3D&                          otherPos,
    const Vector3D&                          otherSize) noexcept
{
    Vector3 BoundingBox1_1 = { pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 };
    Vector3 BoundingBox1_2 = { pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 };
    Vector3 BoundingBox2_1 = {
        otherPos.x - otherSize.x / 2, otherPos.y - otherSize.y / 2, otherPos.z - otherSize.z / 2
    };
    Vector3 BoundingBox2_2 = {
        otherPos.x + otherSize.x / 2, otherPos.y + otherSize.y / 2, otherPos.z + otherSize.z / 2
    };

    BoundingBox BoundingBox1 = { BoundingBox1_1, BoundingBox1_2 };
    BoundingBox BoundingBox2 = { BoundingBox2_1, BoundingBox2_2 };

    return (CheckCollisionBoxes(BoundingBox1, BoundingBox2));
}