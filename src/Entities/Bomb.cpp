/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

Bomb::Bomb(Vector3 pos, Player* p) noexcept
{
    position  = pos;
    type      = EntityType::BOMB;
    color     = BLUE;
    lifeTime  = 2.0f;
    lifeTimer = std::make_unique<Timer>(lifeTime);
    explosion = nullptr;
    player    = p;
    hitbox    = nullptr;
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

bool Bomb::isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    if (explosion == nullptr) return false;
    return explosion->isColliding(others);
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
    lifeTimer->updateTimer();

    if (!lifeTimer->timerDone()) {
        display();
        return false;
    } else {
        if (explosion == nullptr) explosion = std::make_unique<Explosion>(position, 20.0f);
        if (explosion->update()) {
            player->nbBomb++;
            return true;
        }
        return false;
    }
}