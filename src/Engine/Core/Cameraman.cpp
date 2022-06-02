/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#include "Cameraman.hpp"

#include <math.h>

#include <cmath>
#include <iostream>

#include "Error.hpp"
#include "Round.hpp"

Cameraman::Cameraman() noexcept
    : isMoving(false)
    , speed(10.0f)
{
    fovy       = 60.0f;
    projection = CAMERA_PERSPECTIVE;
}

void Cameraman::moveX(const float& x) noexcept
{
    position.x += Round::round(x * GetFrameTime(), 1);
}

void Cameraman::moveY(const float& y) noexcept
{
    position.y += Round::round(y * GetFrameTime(), 1);
}

void Cameraman::moveZ(const float& z) noexcept
{
    position.z += Round::round(z * GetFrameTime(), 1);
}

void Cameraman::moveTo(const Vector3& to, const Vector3& target, const Vector3& up) noexcept
{
    targetPosition = to;
    targetTarget   = target;
    targetUp       = up;
    isMoving       = true;
}

void Cameraman::tpTo(const Vector3& to, const Vector3& tar, const Vector3& newUp) noexcept
{
    position = to;
    target   = tar;
    up       = newUp;
    isMoving = false;
}

bool Cameraman::smoothMove(void) noexcept
{
    bool    thereIsMovement = false;
    Vector3 roundPos        = Round::roundVector(position, 1);
    Vector3 roundTarget     = Round::roundVector(targetPosition, 1);
    Vector3 dir             = { (roundPos.x < roundTarget.x) ? 1.0f : -1.0f,
        (roundPos.y < roundTarget.y) ? 1.0f : -1.0f,
        (roundPos.z < roundTarget.z) ? 1.0f : -1.0f };

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

void Cameraman::lookBetweenEntities(std::vector<std::unique_ptr<Entities>>& entities)
{
    float minX = INFINITY;
    float minZ = INFINITY;
    float maxX = -minX;
    float maxZ = -minZ;

    for (auto& entity : entities) {
        if (!entity->getEnabledValue()) continue;
        auto transform = entity->getComponent<Transform3D>();
        if (!transform.has_value()) throw(Error("Error in camera handling.\n"));

        Vector3 pos = transform->get().getPosition();
        if (pos.x < minX) minX = pos.x;
        if (pos.x > maxX) maxX = pos.x;
        if (pos.z < minZ) minZ = pos.z;
        if (pos.z > maxZ) maxZ = pos.z;
    }

    float newX = (minX + maxX) / 2;
    float newZ = (minZ + maxZ) / 2;

    target.x   = newX;
    target.z   = newZ;
    position.x = newX;
    position.z = newZ + 2.0f;
}
