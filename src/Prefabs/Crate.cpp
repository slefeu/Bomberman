/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

#include "Item.hpp"

Crate::Crate(Vector3 pos, std::unique_ptr<Render3D>* newModel, GameData* data) noexcept
    : Box(pos, { 1.0f, 1.0f, 1.0f })
    , data(data)
{
    type             = EntityType::E_CRATE;
    hitbox->position = { position.x, 0.35f, position.z };
    hitbox->size     = { 1.0f, 1.0f, 1.0f };
    scale            = 0.015f;
    position.y       = 0 - scale;
    isEnable         = true;
    model            = newModel;

    hitbox->update(hitbox->position);
}

void Crate::display() noexcept
{
    if (!isEnable) return;
    DrawModel(MODEL->model, position, scale, WHITE);
    hitbox->display();
}

void Crate::dropItem() noexcept
{
    if (rand() % 3 != 0) return;
    data->items->emplace_back(std::make_unique<Item>(position, data));
}