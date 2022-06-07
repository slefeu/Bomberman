/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Cameraman
*/

#include "Cameraman.hpp"

#include <math.h>

#include <cmath>

#include "Error.hpp"
#include "Round.hpp"

Cameraman::Cameraman() noexcept
    : isMoving(false)
    , speed(0.5f)
{
    camera.fovy       = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Cameraman::moveX(const float& x) noexcept
{
    camera.position.x += x;
}

void Cameraman::moveY(const float& y) noexcept
{
    camera.position.y += y;
}

void Cameraman::moveZ(const float& z) noexcept
{
    camera.position.z += z;
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
    camera.position = to;
    camera.target   = tar;
    camera.up       = newUp;
    isMoving        = false;
}

bool Cameraman::smoothMove() noexcept
{
    bool    thereIsMovement = false;
    Vector3 roundPos        = Round::roundVector(camera.position, 1);
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

    camera.target = targetTarget;
    camera.up     = targetUp;

    return thereIsMovement;
}

void Cameraman::lookBetweenEntity(std::vector<std::unique_ptr<Entity>>& Entity)
{
    float minX = INFINITY;
    float minZ = INFINITY;
    float maxX = -minX;
    float maxZ = -minZ;

    for (auto& entity : Entity) {
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

    camera.target.x   = newX;
    camera.target.z   = newZ;
    camera.position.x = newX;
    camera.position.z = newZ + 2.0f;
}

Vector3 Cameraman::getPosition() const noexcept
{
    return targetPosition;
}

Vector3 Cameraman::getTarget() const noexcept
{
    return targetTarget;
}

Vector3 Cameraman::getUp() const noexcept
{
    return targetUp;
}

bool Cameraman::getIsMoving() const noexcept
{
    return isMoving;
}

float Cameraman::getSpeed() const noexcept
{
    return speed;
}

Camera3D Cameraman::getCamera() const noexcept
{
    return camera;
}

void Cameraman::setPosition(const Vector3& pos) noexcept
{
    targetPosition = pos;
}

void Cameraman::setTarget(const Vector3& tar) noexcept
{
    targetTarget = tar;
}

void Cameraman::setUp(const Vector3& up) noexcept
{
    targetUp = up;
}

void Cameraman::setIsMoving(const bool& isMoving) noexcept
{
    this->isMoving = isMoving;
}

void Cameraman::setSpeed(const float& speed) noexcept
{
    this->speed = speed;
}