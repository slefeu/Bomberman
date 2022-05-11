/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#include "Cameraman.hpp"

#include <math.h>

#include <iostream>

#include "Round.hpp"

Cameraman::Cameraman() noexcept
{
    fovy       = 60.0f;
    projection = CAMERA_PERSPECTIVE;
    isMoving   = false;
    speed      = 10.0f;
}

void Cameraman::moveX(float x) noexcept
{
    position.x += Round().round(x * GetFrameTime(), 1);
}

void Cameraman::moveY(float y) noexcept
{
    position.y += Round().round(y * GetFrameTime(), 1);
}

void Cameraman::moveZ(float z) noexcept
{
    position.z += Round().round(z * GetFrameTime(), 1);
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
    bool thereIsMovement = false;

    Vector3 roundPos;
    Vector3 roundTarget;

    roundPos.x = Round().round(position.x, 1);
    roundPos.y = Round().round(position.y, 1);
    roundPos.z = Round().round(position.z, 1);

    roundTarget.x = Round().round(targetPosition.x, 1);
    roundTarget.y = Round().round(targetPosition.y, 1);
    roundTarget.z = Round().round(targetPosition.z, 1);

    Vector3 dir;
    dir.x = (roundPos.x < roundTarget.x) ? 1.0f : -1.0f;
    dir.y = (roundPos.y < roundTarget.y) ? 1.0f : -1.0f;
    dir.z = (roundPos.z < roundTarget.z) ? 1.0f : -1.0f;

    if ((dir.z == 1 && roundTarget.z > roundPos.z) || (dir.z == -1 && roundTarget.z < roundPos.z)) {
        thereIsMovement = true;
        moveZ(dir.z * speed);
    }
    if ((dir.x == 1 && roundTarget.x > roundPos.x) || (dir.x == -1 && roundTarget.x < roundPos.x)) {
        thereIsMovement = true;
        moveX(dir.x * speed);
    }
    if ((dir.y == 1 && roundTarget.y > roundPos.y) || (dir.y == -1 && roundTarget.y < roundPos.y)) {
        thereIsMovement = true;
        moveY(dir.y * speed);
    }

    target = targetTarget;
    up     = targetUp;

    return thereIsMovement;
}

void Cameraman::lookBetweenEntities(std::vector<std::unique_ptr<Entities>>& entities) noexcept
{
    float minX = 1 / 0.f;
    float minZ = 1 / 0.f;
    float maxX = -minX;
    float maxZ = -minZ;

    for (auto& entity : entities) {
        if (!entity->isEnable) continue;
        Vector3 pos = entity->getPosition();
        if (pos.x < minX) minX = pos.x;
        if (pos.x > maxX) maxX = pos.x;
        if (pos.z < minZ) minZ = pos.z;
        if (pos.z > maxZ) maxZ = pos.z;
    }

    float newX = (minX + maxX) / 2;
    float newZ = (minZ + maxZ) / 2;

    std::cout << newX << " " << newZ << std::endl;

    target.x   = newX;
    target.z   = newZ;
    position.x = newX;
    position.z = newZ + 2.0f;
}