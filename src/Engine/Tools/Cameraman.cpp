/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#include "Cameraman.hpp"

#include <math.h>

#include <iostream>

Cameraman::Cameraman() noexcept
{
    fovy       = 60.0f;
    projection = CAMERA_PERSPECTIVE;
    isMoving   = false;
    speed      = 1;
}

void Cameraman::moveX(float x) noexcept
{
    position.x += x;
}

void Cameraman::moveY(float y) noexcept
{
    position.y += y;
}

void Cameraman::moveZ(float z) noexcept
{
    position.z += z;
}

void Cameraman::moveTo(Vector3 to, Vector3 target, Vector3 up) noexcept
{
    targetPosition = to;
    targetTarget   = target;
    targetUp       = up;
    isMoving       = true;
}

void Cameraman::tpTo(Vector3 to, Vector3 tar, Vector3 newUp) noexcept
{
    position = to;
    target   = tar;
    up       = newUp;
    isMoving = false;
}

bool Cameraman::smoothMove(void) noexcept
{
    Vector3 dir;
    dir.x = (position.x < targetPosition.x) ? 1.0f : -1.0f;
    dir.y = (position.y < targetPosition.y) ? 1.0f : -1.0f;
    dir.z = (position.z < targetPosition.z) ? 1.0f : -1.0f;

    if (position.x == targetPosition.x && position.y == targetPosition.y && position.z == targetPosition.z) return false;
    if (targetPosition.x != position.x) moveX(dir.x * speed);
    if (targetPosition.y != position.y) moveY(dir.y * speed);
    if (targetPosition.z != position.z) moveZ(dir.z * speed);

    target = targetTarget;
    up     = targetUp;

    return true;
}

void Cameraman::lookBetweenEntities(std::vector<std::unique_ptr<Entities>>& entities) noexcept
{
    float minX = 1 / 0.f;
    float minZ = 1 / 0.f;
    float maxX = -minX;
    float maxZ = -minZ;

    for (auto& entity : entities) {
        Vector3 pos = entity->getPosition();
        if (pos.x < minX) minX = pos.x;
        if (pos.x > maxX) maxX = pos.x;
        if (pos.z < minZ) minZ = pos.z;
        if (pos.z > maxZ) maxZ = pos.z;
    }

    target.x = (minX + maxX) / 2;
    target.z = (minZ + maxZ) / 2;
}