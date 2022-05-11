/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#include "Box.hpp"

Box::Box(Vector3 pos, float newScale) noexcept
{
    position  = pos;
    isSolid   = true;
    isTrigger = false;
    type      = EntityType::BOX;
    // scale     = newScale;

    // model                                                 = LoadModel("Assets/Models/box.obj");
    // texture                                               = LoadTexture("Assets/Textures/box.png");
    // model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    // position.y += scale;
    (void)newScale;
    color = GREEN;
    size  = { (rand() % 10) / 10.0f, (rand() % 10) / 10.0f, (rand() % 10) / 10.0f };
}

void Box::display() noexcept
{
    DrawCubeV(position, size, color);
    // DrawModel(model, position, scale, WHITE);
}

void Box::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Box::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Box::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

void Box::action(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    (void)others;
    return;
}

Vector3 Box::getPosition() noexcept
{
    return position;
}

Vector3 Box::getSize() noexcept
{
    return size;
}

bool Box::isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept
{
    (void)others;
    (void)pos;
    return false;
}

bool Box::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}