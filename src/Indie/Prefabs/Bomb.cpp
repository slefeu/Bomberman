/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

#include <iostream>

Bomb::Bomb(Vector3                              pos,
    Player*                                     p,
    std::unique_ptr<Model3D>*                   newModel,
    int                                         bombSize,
    GameData*                                   data,
    std::vector<std::unique_ptr<GameObject3D>>* entities) noexcept
    : lifeTime(3.0f)
    , lifeTimer(NEW_TIMER(lifeTime))
    , player(p)
    , size(bombSize)
    , hasHitbox(false)
    , data(data)
    , entities(entities)
{
    transform3d.setScale(0.07f);
    transform3d.setPosition({ round(pos.x), 0.0f - transform3d.getScale(), round(pos.z) });
    render.setRenderType(RenderType::R_3DMODEL);
    render.setModel(newModel);

    type               = EntityType::E_BOMB;
    Vector3 hitboxsize = { 0.8f, 1.2f, 0.8f };
    hitbox             = NEW_HITBOX(transform3d.getPosition(), hitboxsize, false);
}

void Bomb::Display() noexcept
{
    render.display(transform3d);
}

void Bomb::Update() noexcept
{
    lifeTimer->updateTimer();

    if (lifeTimer->timerDone()) {
        explode();
        return;
    }

    if (fires.size() == 0 && !hitbox->isSolid) {
        if (data->players.size() <= 0) return;
        int i = 0;

        for (auto& other : data->players) {
            if (other->hitbox == nullptr) continue;
            if (!hitbox->isColliding(other->hitbox)) i++;
        }

        if (i == (int)data->players.size()) hitbox->isSolid = true;
        return;
    }
}

void Bomb::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    (void)other;
}

void Bomb::explode() noexcept
{
    if (isExploding) return;

    isExploding     = true;
    hitbox->isSolid = false;
    player->nbBomb++;
    fires.emplace_back(NEW_FIRE(transform3d.getPosition(), 0.9f));
    createFire({ 1.0f, 0.0f, 0.0f });
    createFire({ -1.0f, 0.0f, 0.0f });
    createFire({ 0.0f, 0.0f, 1.0f });
    createFire({ 0.0f, 0.0f, -1.0f });

    for (auto& fire : fires) { entities->emplace_back(std::move(fire)); }
    isEnable = false;
}

void Bomb::createFire(Vector3 mul) noexcept
{
    Vector3 position = transform3d.getPosition();
    float   scale    = 0.5f;
    Vector3 newPos;
    bool    exit = false;

    for (int i = 1; i < size && !exit; i++) {
        newPos.x = position.x + (float(i) * mul.x);
        newPos.y = position.y + (float(i) * mul.y);
        newPos.z = position.z + (float(i) * mul.z);
        fires.emplace_back(NEW_FIRE(newPos, scale));

        auto& fire = fires.back();
        for (auto& other : *entities)
            if (fire->hitbox->isColliding(other->hitbox))
                if ((exit = fire->ExplodeElements(other))) break;
    }
}