/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Explosion
*/

#include "Explosion.hpp"

#include <iostream>

#include "Collision.hpp"

Explosion::Explosion(Vector3 pos, float newSize) noexcept
{
    position  = pos;
    isSolid   = false;
    isTrigger = false;
    type      = EntityType::EXPLOSION;
    size      = { newSize, 0.2f, 0.2f };
    color     = RED;
    lifeTime  = 1.0f;
    timer     = std::make_unique<Timer>(lifeTime);
}

void Explosion::display() noexcept
{
    DrawCubeV(position, size, color);
    DrawCubeV(position, { size.z, size.y, size.x }, color);
}

void Explosion::moveX(float x) noexcept
{
    (void)x;
}

void Explosion::moveY(float y) noexcept
{
    (void)y;
}

void Explosion::moveZ(float z) noexcept
{
    (void)z;
}

void Explosion::action(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Explosion::getPosition() noexcept
{
    return position;
}

Vector3 Explosion::getSize() noexcept
{
    return size;
}

bool Explosion::isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept
{
    std::cout << "Explosion::isColliding" << std::endl;
    for (auto& other : others) {
        Vector3 otherPos  = other->getPosition();
        Vector3 otherSize = other->getSize();

        if (other->isSolid) {
            if (Collision().isColliding(pos, size, otherPos, otherSize)) return true;
            if (Collision().isColliding(pos, { size.z, size.y, size.x }, otherPos, otherSize)) return true;
        }
    }
    return false;
}

bool Explosion::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

bool Explosion::update(void) noexcept
{
    display();
    timer->updateTimer();
    return timer->timerDone();
}