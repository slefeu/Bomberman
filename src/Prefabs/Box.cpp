/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(Vector3 pos, Vector3 newSize) noexcept
{
    transform3d.setPosition(pos);
    transform3d.setSize(newSize);

    type   = EntityType::E_BOX;
    hitbox = std::make_unique<BoxCollider>(transform3d.getPosition(), transform3d.getSize(), true);
}

void Box::display() noexcept
{
    DrawCubeV(transform3d.getPosition(), transform3d.getSize(), ORANGE);
    hitbox->update(transform3d.getPosition());
    hitbox->display();
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
