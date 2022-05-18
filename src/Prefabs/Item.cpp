/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

#include <iostream>

#include "Player.hpp"

Item::Item(Vector3 pos, GameData* data) noexcept
{
    Vector3 vectortemp = { 1.0f, 1.0f, 0.5f };
    position           = pos;
    type               = EntityType::E_ITEM;
    hitbox             = std::make_unique<BoxCollider>(position, vectortemp, true);
    scale              = 1.0f;
    hitbox->isSolid    = false;
    itemType           = (ItemType)((int)rand() % 3);

    position.z -= scale / 2;
    hitbox->position.z += scale / 10;

    switch (itemType) {
        case ItemType::I_SPEEDUP: model = MODELS(M_IROLLER); break;
        case ItemType::I_BOMBUP: model = MODELS(M_IBOMB); break;
        case ItemType::I_FIREUP: model = MODELS(M_IFIRE); break;
        default: break;
    }
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
                setPlayerStat((std::unique_ptr<Player>&)other);
                isEnable = false;
            }
        };
    }
    return false;
}

void Item::setPlayerStat(std::unique_ptr<Player>& p) noexcept
{
    switch (itemType) {
        case ItemType::I_SPEEDUP: p->speed += 0.2f; break;
        case ItemType::I_BOMBUP: p->nbBomb += 1; break;
        case ItemType::I_FIREUP: p->bombSize += 1; break;
        default: break;
    }
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
