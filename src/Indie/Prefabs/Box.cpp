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
    hitbox = std::make_unique<BoxCollider>(transform3d.getPosition(), transform3d.getSize(), true);
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

// void Box::display() noexcept
// {
//     render.display(transform3d);
//     hitbox->update(transform3d.getPosition());
//     hitbox->display();
// }

// // -------------------------- USELESS FUNCTIONS --------------------------

// void Box::setLifeTime(float const& newLifeTime) noexcept
// {
//     (void)newLifeTime;
// }

// void Box::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     (void)others;
//     return;
// }

// bool Box::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     (void)others;
//     return false;
// }

// bool Box::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
// {
//     (void)others;
//     (void)xdir;
//     (void)zdir;
//     return false;
// }

// bool Box::update(void) noexcept
// {
//     return false;
// }

// bool Box::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     (void)others;
//     return false;
// }
