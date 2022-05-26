/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(Vector3 pos, Vector3 newSize) noexcept
{
    transform3d.setPosition(pos);
    transform3d.setSize(newSize);
    render.setRenderType(RenderType::R_CUBE);
    render.setColor(BLUE);

    type   = EntityType::E_BOX;
    hitbox = NEW_HITBOX(transform3d.getPosition(), transform3d.getSize(), true);
}

void Box::Display() noexcept
{
    render.display(transform3d);
}

void Box::Update() noexcept
{
    hitbox->update(transform3d.getPosition());
}

void Box::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    (void)other;
}