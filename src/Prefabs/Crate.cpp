/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

Crate::Crate(Vector3 pos, Render3D* newModel) noexcept
    : Box(pos, { 1.0f, 1.0f, 1.0f })
{
    type             = EntityType::CRATE;
    hitbox->position = { position.x, 0.35f, position.z };
    hitbox->size     = { 1.0f, 1.0f, 1.0f };
    scale            = 0.017f;
    position.y       = 0 - scale;
    isEnable         = true;
    model            = newModel;

    hitbox->update(hitbox->position);
}

void Crate::display() noexcept
{
    if (!isEnable) return;
    DrawModel(model->model, position, scale, WHITE);
    hitbox->display();
}