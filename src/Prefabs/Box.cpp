/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(Vector3 pos, Vector3 newSize) noexcept
{
    position = pos;
    type     = EntityType::E_BOX;
    color    = ORANGE;
    size     = newSize;
    hitbox   = std::make_unique<BoxCollider>(position, size, true);
}

void Box::display() noexcept
{
    DrawCubeV(position, size, color);
    hitbox->update(position);
    hitbox->display();
}

void Box::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Box::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Box::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

Vector3 Box::getPosition() noexcept
{
    return position;
}

Vector3 Box::getSize() noexcept
{
    return size;
}

// -------------------------- USELESS FUNCTIONS --------------------------

void Box::setLifeTime(float const& newLifeTime) noexcept
{
    (void)newLifeTime;
}

void Box::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return;
}

bool Box::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}

bool Box::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

bool Box::update(void) noexcept
{
    return false;
}

bool Box::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}
