/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

Crate::Crate(Vector3 pos) noexcept
{
    position   = pos;
    type       = EntityType::CRATE;
    color      = ORANGE;
    hitbox     = std::make_unique<HitBox>((Vector3){ position.x, 0.35f, position.z }, (Vector3){ 0.7f, 0.7f, 0.7f }, true);
    scale      = 0.012f;
    model      = LoadModel("Assets/Models/box.obj");
    texture    = LoadTexture("Assets/Textures/box.png");
    position.y = 0 - scale;
    isEnable   = true;

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

void Crate::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Crate::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Crate::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

void Crate::action(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Crate::getPosition() noexcept
{
    return position;
}

Vector3 Crate::getSize() noexcept
{
    return size;
}

bool Crate::isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    (void)others;
    return false;
}

bool Crate::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}

bool Crate::update(void) noexcept
{
    return false;
}