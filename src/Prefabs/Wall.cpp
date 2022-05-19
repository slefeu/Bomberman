/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(Vector3 pos, std::unique_ptr<Render3D>* model, GameData* data) noexcept
    : Crate(pos, model, data)
{
    type       = EntityType::E_WALL;
    scale      = 0.017f;
    position.y = pos.y;
}

void Wall::display() noexcept
{
    if (!isEnable) return;

    if (position.y > 0) { position.y -= 4.0f * GetFrameTime(); }
    if (position.y < 0) { position.y = 0; }

    DrawModel(MODEL->model, position, scale, WHITE);
    hitbox->display();
    hitbox->update(position);
}