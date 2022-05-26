/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

#include "Collision.hpp"

BoxCollider::BoxCollider(Vector3 newPos, Vector3 newSize, bool solid) noexcept
    : position(newPos)
    , size(newSize)
    , isSolid(solid)
{
}

void BoxCollider::display() noexcept
{
    if (debug) DrawCubeWiresV(position, size, GREEN);
}

void BoxCollider::update(Vector3 newPos) noexcept
{
    position = newPos;
}

bool BoxCollider::isColliding(std::unique_ptr<BoxCollider>& other) noexcept
{
    return Collision().isColliding(position, size, other->position, other->size);
}

bool BoxCollider::isColliding(std::unique_ptr<BoxCollider>& otherHit, Vector3& otherPos) noexcept
{
    return Collision().isColliding(position, size, otherPos, otherHit->size);
}