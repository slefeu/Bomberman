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
    type = EntityType::E_CRATE;

    transform3d.setScale(0.015f);
    transform3d.setY(0 - transform3d.getScale());

    hitbox->position = { transform3d.getPosition().x, 0.35f, transform3d.getPosition().z };
    hitbox->size     = { 1.0f, 1.0f, 1.0f };
    isEnable         = true;
    model            = newModel;

    hitbox->update(hitbox->position);
}

void Crate::display() noexcept
{
    if (!isEnable) return;
    DrawModel(MODEL->model, transform3d.getPosition(), transform3d.getScale(), WHITE);
    hitbox->display();
}

void Crate::dropItem() noexcept
{
    if (rand() % 3 != 0) return;
    data->items->emplace_back(std::make_unique<Item>(transform3d.getPosition(), data));
}