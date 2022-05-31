/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

#include <iostream>

#include "Error.hpp"

Bomb::Bomb(Vector3                          pos,
    Player*                                 p,
    std::unique_ptr<Model3D>*               newModel,
    int                                     bombSize,
    GameData*                               data,
    std::vector<std::unique_ptr<Entities>>* entities)
    : Entities(EntityType::E_BOMB)
    , lifeTime(3.0f)
    , lifeTimer(NEW_TIMER(lifeTime))
    , player(p)
    , size(bombSize)
    , hasHitbox(false)
    , data(data)
    , entities(entities)
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value())
        throw(Error("Error, could not instanciate the bomb element.\n"));
    transform->get().setScale(0.07f);
    transform->get().setPosition(
        { round(pos.x), 0.0f - transform->get().getScale(), round(pos.z) });
    auto renderer = getComponent<Render>();
    if (!renderer.has_value())
        throw(Error("Error, could not instanciate the bomb element.\n"));
    renderer->get().setRenderType(RenderType::R_3DMODEL);
    renderer->get().setModel(newModel);

    Vector3 hitbox_size = { 0.8f, 1.2f, 0.8f };
    addComponent(
        BoxCollider(transform->get().getPosition(), hitbox_size, false));
}

void Bomb::Display()
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!renderer.has_value() || !transform.has_value())
        throw(Error("Error in displaying a bomb element.\n"));
    renderer->get().display(transform->get());
}

void Bomb::Update()
{
    int  i      = 0;
    auto hitbox = getComponent<BoxCollider>();
    if (!hitbox.has_value())
        throw(Error("Error in updating a bomb element.\n"));

    lifeTimer->updateTimer();
    if (lifeTimer->timerDone()) {
        explode();
        return;
    }
    if (fires.size() == 0 && !hitbox->get().getIsSolid()) {
        if (data->players.size() <= 0) return;

        for (auto& other : data->players) {
            if (!(other->getComponent<BoxCollider>().has_value())) continue;
            auto other_collider = other->getComponent<BoxCollider>();
            if (!hitbox->get().isColliding(other_collider->get())) i++;
        }
        if (i == static_cast<int>(data->players.size()))
            hitbox->get().setIsSolid(true);
    }
}

void Bomb::explode() noexcept
{
    auto hitbox = getComponent<BoxCollider>();

    if (is_exploding_) return;
    is_exploding_ = true;
    hitbox->get().setIsSolid(false);
    player->nbBomb++;
    fires.emplace_back(
        NEW_FIRE(getComponent<Transform3D>()->get().getPosition(), 0.9f));
    createFire({ 1.0f, 0.0f, 0.0f });
    createFire({ -1.0f, 0.0f, 0.0f });
    createFire({ 0.0f, 0.0f, 1.0f });
    createFire({ 0.0f, 0.0f, -1.0f });

    for (auto& fire : fires) { entities->emplace_back(std::move(fire)); }
    setEnabledValue(false);
}

void Bomb::createFire(Vector3 mul) noexcept
{
    Vector3 position = getComponent<Transform3D>()->get().getPosition();
    float   scale    = 0.5f;
    Vector3 newPos;
    bool    exit = false;

    for (int i = 1; i < size && !exit; i++) {
        newPos.x = position.x + (float(i) * mul.x);
        newPos.y = position.y + (float(i) * mul.y);
        newPos.z = position.z + (float(i) * mul.z);
        fires.emplace_back(NEW_FIRE(newPos, scale));

        auto& fire = fires.back();
        for (auto& other : *entities) {
            auto collider      = fire->getComponent<BoxCollider>();
            auto other_collide = other->getComponent<BoxCollider>();
            if (collider->get().isColliding(other_collide->get()))
                if ((exit = fire->ExplodeElements(other))) break;
        }
    }
}

void Bomb::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    (void)other;
}