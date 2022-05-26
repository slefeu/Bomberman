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
    transform3d.setScale(0.07f);
    transform3d.setPosition({ round(pos.x), 0.0f - transform3d.getScale(), round(pos.z) });
    render.setRenderType(RenderType::R_3DMODEL);
    render.setModel(newModel);

    type               = EntityType::E_BOMB;
    Vector3 hitboxsize = { 0.8f, 1.2f, 0.8f };
    hitbox             = std::make_unique<BoxCollider>(transform3d.getPosition(), hitboxsize, false);
}

void Bomb::display() noexcept
{
    render.display(transform3d);
    // DrawModel(MODEL->model, transform3d.getPosition(), transform3d.getScale(), WHITE);
    hitbox->update(transform3d.getPosition());
    hitbox->display();
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
    if (explosion == nullptr) explosion = std::make_unique<Explosion>(transform3d.getPosition(), size, others);
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
