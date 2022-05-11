/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(Vector3 pos) noexcept
{
    position  = pos;
    isSolid   = false;
    isTrigger = false;
    type      = EntityType::BOMB;
    color     = BLUE;
    lifeTime  = 2.0f;
    timer     = std::make_unique<Timer>(lifeTime);
    position.y += 0.1f;
}

void Bomb::display() noexcept
{
    DrawSphere(position, 0.2f, color);
}

void Bomb::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Bomb::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Bomb::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

void Bomb::action(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Bomb::getPosition() noexcept
{
    return position;
}

Vector3 Bomb::getSize() noexcept
{
    return size;
}

bool Bomb::isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept
{
    (void)others;
    (void)pos;
    return false;
}

bool Bomb::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

bool Bomb::update(void) noexcept
{
    display();
    timer->updateTimer();
    return timer->timerDone();
}