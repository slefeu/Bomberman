/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(Vector3 pos, std::unique_ptr<Model3D>* model) noexcept
    : Crate(pos, model, nullptr, nullptr)
{
    type = EntityType::E_WALL;

    transform3d.setScale(0.017f);
    transform3d.setY(pos.y);
}

void Wall::Update() noexcept
{
    if (!isEnable) return;

    if (transform3d.getPosition().y > 0) { transform3d.moveY(-4.0f); }
    if (transform3d.getPosition().y < 0) { transform3d.setY(0.0f); }

    hitbox->update(transform3d.getPosition());
}