/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** HitBox
*/

#include "HitBox.hpp"

#include "Collision.hpp"

HitBox::HitBox(Vector3 newPos, Vector3 newSize, bool solid) noexcept
    : position(newPos)
    , size(newSize)
    , isSolid(solid)
{
}

void HitBox::display() noexcept
{
    if (debug) DrawCubeWiresV(position, size, GREEN);
}

void HitBox::update(Vector3 newPos) noexcept
{
    position = newPos;
}

bool HitBox::isColliding(std::unique_ptr<HitBox>& other) noexcept
{
    return Collision().isColliding(position, size, other->position, other->size);
}

bool HitBox::isColliding(std::unique_ptr<HitBox>& otherHit, Vector3& otherPos) noexcept
{
    return Collision().isColliding(position, size, otherPos, otherHit->size);
}