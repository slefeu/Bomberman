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
    type = EntityType::E_WALL;

    transform3d.setScale(0.017f);
    transform3d.setY(pos.y);
    // render.setRenderType(RenderType::R_3DMODEL);
    // render.setModel(model);
}

void Wall::display() noexcept
{
    if (!isEnable) return;

    if (transform3d.getPosition().y > 0) { transform3d.moveY(-4.0f); }
    if (transform3d.getPosition().y < 0) { transform3d.setY(0.0f); }

    render.display(transform3d);
    // DrawModel(MODEL->model, transform3d.getPosition(), transform3d.getScale(), WHITE);
    hitbox->display();
    hitbox->update(transform3d.getPosition());
}