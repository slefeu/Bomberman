/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

#include "Item.hpp"

Crate::Crate(Vector3 pos, std::unique_ptr<Model3D>* newModel, GameData* data) noexcept
    : Box(pos, { 1.0f, 1.0f, 1.0f })
    , data(data)
{
    type     = EntityType::E_CRATE;
    isEnable = true;

    transform3d.setScale(0.015f);
    transform3d.setY(0 - transform3d.getScale());
    render.setRenderType(RenderType::R_3DMODEL);
    render.setModel(newModel);

    hitbox->position = { transform3d.getPosition().x, 0.35f, transform3d.getPosition().z };
    hitbox->size     = { 1.0f, 1.0f, 1.0f };
    hitbox->update(hitbox->position);
}

void Crate::Display() noexcept
{
    if (!isEnable) return;

    render.display(transform3d);
}

void Crate::Update() noexcept
{
    if (!isEnable) return;
}

void Crate::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    (void)other;
}

// void Crate::display() noexcept
// {
//     if (!isEnable) return;
//     render.display(transform3d);
// }

void Crate::dropItem() noexcept
{
    if (rand() % 3 != 0) return;
    data->items->emplace_back(std::make_unique<Item>(transform3d.getPosition(), data));
}