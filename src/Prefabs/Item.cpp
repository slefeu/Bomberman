/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

#include <iostream>

#include "Player.hpp"

Item::Item(Vector3 pos, std::unique_ptr<Render3D>* newModel) noexcept
{
    position = pos;
    type     = EntityType::E_ITEM;
    hitbox   = std::make_unique<BoxCollider>(position, (Vector3){ 1.0f, 1.0f, 0.5f }, true);
    model    = newModel;
    scale    = 1.0f;

    position.z -= scale / 2;
    hitbox->position.z += scale / 10;
    hitbox->isSolid = false;
}

void Item::display() noexcept
{
    if (!isEnable) return;
    DrawModelEx(MODEL->model, position, { 1.0f, 0.0f, 0.0f }, 90.0f, { scale, scale, scale }, WHITE);
    hitbox->update(hitbox->position);
    hitbox->display();
}

bool Item::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    if (!isEnable) return false;
    for (auto& other : others) {
        if (hitbox == nullptr || other->hitbox == nullptr) continue;
        if (hitbox->isColliding(other->hitbox)) {
            if (other->type == EntityType::E_PLAYER) {
                std::unique_ptr<Player>& p = (std::unique_ptr<Player>&)other;
                p->setStats(1, 1, 1);
                isEnable = false;
            }
        };
    }
    return false;
}

// -------------------------- USELESS FUNCTIONS --------------------------

void Item::moveX(float x) noexcept
{
    (void)x;
}

void Item::moveY(float y) noexcept
{
    (void)y;
}

void Item::moveZ(float z) noexcept
{
    (void)z;
}

void Item::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Item::getPosition() noexcept
{
    return position;
}

Vector3 Item::getSize() noexcept
{
    return size;
}

bool Item::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

bool Item::update(void) noexcept
{
    return false;
}

bool Item::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}
