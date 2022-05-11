/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Explosion
*/

#include "Explosion.hpp"

#include <iostream>

#include "Collision.hpp"

Explosion::Explosion(Vector3 posi, float newSize) noexcept
{
    position  = posi;
    isSolid   = false;
    isTrigger = false;
    type      = EntityType::EXPLOSION;
    size      = { newSize, 0.2f, 0.2f };
    color     = RED;
    lifeTime  = 1.0f;
    timer     = std::make_unique<Timer>(lifeTime);

    pos[0] = { position.x - size.x / 4, position.y, position.z };
    pos[1] = { position.x + size.x / 4, position.y, position.z };
    pos[2] = { position.x, position.y, position.z - size.x / 4 };
    pos[3] = { position.x, position.y, position.z + size.x / 4 };

    siz[0] = { size.x / 2, size.y, size.z };
    siz[1] = { size.x / 2, size.y, size.z };
    siz[2] = { size.z, size.y, size.x / 2 };
    siz[3] = { size.z, size.y, size.x / 2 };
}

void Explosion::display() noexcept
{
    for (int i = 0; i < 4; i++) DrawCubeV(pos[i], siz[i], color);
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

bool Explosion::isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& posi) noexcept
{
    (void)posi;
    bool isColliding = false;

    for (auto& other : others) {
        Vector3 otherPos  = other->getPosition();
        Vector3 otherSize = other->getSize();

        if (other->isSolid) {
            if (Collision().isColliding(pos[0], siz[0], otherPos, otherSize)
                || Collision().isColliding(pos[1], siz[1], otherPos, otherSize)
                || Collision().isColliding(pos[2], siz[2], otherPos, otherSize)
                || Collision().isColliding(pos[3], siz[3], otherPos, otherSize)) {
                if (other->type == EntityType::PLAYER) other->isEnable = false;
                isColliding = true;
            }
        }
    }
    return isColliding;
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