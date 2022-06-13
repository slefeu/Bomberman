/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Cameraman
*/

#include "Cameraman.hpp"

#include "Round.hpp"

Cameraman::Cameraman() noexcept
{
    camera_.fovy       = 60.0f;
    camera_.projection = CAMERA_PERSPECTIVE;
}

void Cameraman::moveX(float x) noexcept
{
    camera_.position.x += x;
}

void Cameraman::moveY(float y) noexcept
{
    camera_.position.y += y;
}

void Cameraman::moveZ(float z) noexcept
{
    camera_.position.z += z;
}

void Cameraman::moveTo(const Vector3D& to, const Vector3D& target, const Vector3D& up) noexcept
{
    position_  = to;
    target_    = target;
    up_        = up;
    is_moving_ = true;
}

void Cameraman::tpTo(const Vector3D& to, const Vector3D& tar, const Vector3D& newUp) noexcept
{
    camera_.position.x = to.x;
    camera_.position.y = to.y;
    camera_.position.z = to.z;

    camera_.target.x = tar.x;
    camera_.target.y = tar.y;
    camera_.target.z = tar.z;

    camera_.up.x = newUp.x;
    camera_.up.y = newUp.y;
    camera_.up.z = newUp.z;

    is_moving_ = false;
}

bool Cameraman::smoothMove() noexcept
{
    bool     thereIsMovement = false;
    Vector3D roundPos        = { Round::round(camera_.position.x, 1),
        Round::round(camera_.position.y, 1),
        Round::round(camera_.position.z, 1) };
    Vector3D roundTarget     = Round::roundVector(position_, 1);
    Vector3D dir             = { (roundPos.x < roundTarget.x) ? 1.0f : -1.0f,
        (roundPos.y < roundTarget.y) ? 1.0f : -1.0f,
        (roundPos.z < roundTarget.z) ? 1.0f : -1.0f };

    if ((dir.z == 1 && roundTarget.z > roundPos.z) || (dir.z == -1 && roundTarget.z < roundPos.z)) {
        thereIsMovement = true;
        moveZ(dir.z * speed_);
    }
    if ((dir.x == 1 && roundTarget.x > roundPos.x) || (dir.x == -1 && roundTarget.x < roundPos.x)) {
        thereIsMovement = true;
        moveX(dir.x * speed_);
    }
    if ((dir.y == 1 && roundTarget.y > roundPos.y) || (dir.y == -1 && roundTarget.y < roundPos.y)) {
        thereIsMovement = true;
        moveY(dir.y * speed_);
    }

    camera_.target.x = target_.x;
    camera_.target.y = target_.y;
    camera_.target.z = target_.z;

    camera_.up.x = up_.x;
    camera_.up.y = up_.y;
    camera_.up.z = up_.z;

    return (thereIsMovement);
}

Vector3D Cameraman::getPosition() const noexcept
{
    return position_;
}

Vector3D Cameraman::getTarget() const noexcept
{
    return target_;
}

Vector3D Cameraman::getUp() const noexcept
{
    return up_;
}

bool Cameraman::getIsMoving() const noexcept
{
    return is_moving_;
}

void Cameraman::begin3D() const noexcept
{
    BeginMode3D(camera_);
}

void Cameraman::end3D() const noexcept
{
    EndMode3D();
}

void Cameraman::setPosition(const Vector3D& pos) noexcept
{
    position_ = pos;
}

void Cameraman::setIsMoving(bool value) noexcept
{
    is_moving_ = value;
}
