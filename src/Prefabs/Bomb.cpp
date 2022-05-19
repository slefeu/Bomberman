/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

#include <iostream>

Bomb::Bomb(Vector3 pos, Player* p, std::unique_ptr<Render3D>* newModel, int bombSize) noexcept
    : lifeTime(3.0f)
    , lifeTimer(std::make_unique<Timer>(lifeTime))
    , explosion(nullptr)
    , player(p)
    , size(bombSize)
    , hasHitbox(false)
{
    scale              = 0.07f;
    position.x         = round(pos.x);
    position.y         = 0 - scale;
    position.z         = round(pos.z);
    type               = EntityType::E_BOMB;
    model              = newModel;
    Vector3 hitboxsize = { 0.8f, 1.2f, 0.8f };
    hitbox             = std::make_unique<BoxCollider>(position, hitboxsize, false);
}

void Bomb::display() noexcept
{
    DrawModel(MODEL->model, position, scale, WHITE);
    hitbox->update(position);
    hitbox->display();
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

Vector3 Bomb::getPosition() noexcept
{
    return position;
}

Vector3 Bomb::getSize() noexcept
{
    return { 0.0f, 0.0f, 0.0f };
}

bool Bomb::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    if (explosion == nullptr) {
        // Permet de ne pas activer les collisions de la bombe si un joueur est à l'interieur

        if (hitbox->isSolid) return false;
        if (others.size() <= 0 || others[0]->type != EntityType::E_PLAYER) return false;

        int i = 0;

        for (auto& other : others) {
            if (other->hitbox == nullptr) continue;
            if (!hitbox->isColliding(other->hitbox)) i++;
        }

        std::cout << "i = " << i << std::endl;
        std::cout << "hitbox->isSolid = " << hitbox->isSolid << std::endl;

        if (i == (int)others.size()) hitbox->isSolid = true;

        return false;
    }

    return explosion->isColliding(others);
}

bool Bomb::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    lifeTimer->updateTimer();

    if (!lifeTimer->timerDone()) {
        display();
        return false;
    }
    if (explosion == nullptr) explosion = std::make_unique<Explosion>(position, size, others);
    if (explosion->update()) {
        player->nbBomb++;
        return true;
    }
    return false;
}

bool Bomb::update(void) noexcept
{
    lifeTimer->updateTimer();

    if (!lifeTimer->timerDone()) { display(); }
    return false;
}

void Bomb::setLifeTime(float const& newLifeTime) noexcept
{
    lifeTimer->setLifeTime(newLifeTime);
}
// -------------------------- USELESS FUNCTIONS --------------------------

bool Bomb::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

void Bomb::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return;
}
