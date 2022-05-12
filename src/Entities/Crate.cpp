/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

Crate::Crate(Vector3 pos) noexcept
    : Box(pos, { 1.0f, 1.0f, 1.0f })
{
    type             = EntityType::CRATE;
    hitbox->position = { position.x, 0.35f, position.z };
    hitbox->size     = { 0.7f, 0.7f, 0.7f };
    scale            = 0.012f;
    model            = LoadModel("Assets/Models/box.obj");
    texture          = LoadTexture("Assets/Textures/box.png");
    position.y       = 0 - scale;
    isEnable         = true;

    hitbox->update(hitbox->position);

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Crate::~Crate() noexcept
{
    UnloadTexture(texture);
    UnloadModel(model);
}

void Crate::display() noexcept
{
    if (!isEnable) return;
    DrawModel(model, position, scale, WHITE);
    hitbox->display();
}