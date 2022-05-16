/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** Fire.cpp
** File description:
** Fire
*/

#include "Fire.hpp"

#include "Crate.hpp"

Fire::Fire(Vector3 posi, float newSize) noexcept
{
    position = posi;
    type     = EntityType::E_FIRE;
    size     = { newSize, newSize, newSize };
    color    = RED;
    lifeTime = 1.0f;
    timer    = std::make_unique<Timer>(lifeTime);
    hitbox   = std::make_unique<BoxCollider>(position, size, true);
}

bool Fire::update(void) noexcept
{
    display();
    timer->updateTimer();
    return timer->timerDone();
}

bool Fire::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    bool isColliding = false;

    for (auto& other : others) {
        if (other->hitbox == nullptr || hitbox == nullptr) continue;
        if (!other->hitbox->isSolid || !hitbox->isSolid) continue;
        if (hitbox->isColliding(other->hitbox)) {
            CollideAction(other);
            isColliding = true;
        }
    }
    return isColliding;
}

void Fire::CollideAction(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_PLAYER) other->isEnable = false;
    if (other->type == EntityType::E_CRATE) {
        ((std::unique_ptr<Crate>&)other)->dropItem();

        other->isEnable = false;
        other->hitbox.reset();
        other->hitbox = nullptr;
    }
    if (other->type == EntityType::E_ITEM) other->isEnable = false;
}

void Fire::display() noexcept
{
    DrawCubeV(position, size, color);
    hitbox->display();
    hitbox->update(position);
}

// -------------------------- USELESS FUNCTIONS --------------------------

bool Fire::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}

void Fire::moveX(float x) noexcept
{
    (void)x;
}

void Fire::moveY(float y) noexcept
{
    (void)y;
}

void Fire::moveZ(float z) noexcept
{
    (void)z;
}

void Fire::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Fire::getPosition() noexcept
{
    return position;
}

Vector3 Fire::getSize() noexcept
{
    return size;
}

bool Fire::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}
