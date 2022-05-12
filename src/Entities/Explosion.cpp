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
    type      = EntityType::EXPLOSION;
    size      = { newSize, 0.2f, 0.2f };
    color     = RED;
    lifeTime  = 1.0f;
    timer     = std::make_unique<Timer>(lifeTime);
    pos[0]    = { position.x - size.x / 4, position.y, position.z };
    pos[1]    = { position.x + size.x / 4, position.y, position.z };
    pos[2]    = { position.x, position.y, position.z - size.x / 4 };
    pos[3]    = { position.x, position.y, position.z + size.x / 4 };
    siz[0]    = { size.x / 2, size.y, size.z };
    siz[1]    = { size.x / 2, size.y, size.z };
    siz[2]    = { size.z, size.y, size.x / 2 };
    siz[3]    = { size.z, size.y, size.x / 2 };
    hitBoxHor = std::make_unique<HitBox>(position, size, true);
    hitBoxVer = std::make_unique<HitBox>(position, (Vector3){ size.z, size.y, size.x }, true);
}

void Explosion::display() noexcept
{
    for (int i = 0; i < 4; i++) DrawCubeV(pos[i], siz[i], color);
    hitBoxHor->display();
    hitBoxVer->display();
    hitBoxHor->update(position);
    hitBoxVer->update(position);
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

bool Explosion::isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    bool isColliding = false;

    for (auto& other : others) {
        if (other->hitbox == nullptr || hitBoxHor == nullptr || hitBoxVer == nullptr) continue;
        if (!other->hitbox->isSolid || !hitBoxHor->isSolid || !hitBoxVer->isSolid) continue;
        if (hitBoxHor->isColliding(other->hitbox) || hitBoxVer->isColliding(other->hitbox)) {
            if (other->type == EntityType::PLAYER) other->isEnable = false;
            if (other->type == EntityType::CRATE) {
                std::cout << "Crate destroyed" << std::endl;
                other->isEnable = false;
                other->hitbox.reset();
                other->hitbox = nullptr;
            }
            isColliding = true;
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