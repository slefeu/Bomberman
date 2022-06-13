/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

#include "raylib.h"

BoxCollider::BoxCollider(const Vector3D& newPos, const Vector3D& newSize, bool solid) noexcept
    : position_(newPos)
    , size_(newSize)
    , is_solid_(solid)
{
}

bool BoxCollider::checkCollision(const Vector3D& pos,
    const Vector3D&                              size,
    const Vector3D&                              otherPos,
    const Vector3D&                              otherSize) const noexcept
{
    Vector3 BoundingBox1_1 = { pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 };
    Vector3 BoundingBox1_2 = { pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 };
    Vector3 BoundingBox2_1 = {
        otherPos.x - otherSize.x / 2, otherPos.y - otherSize.y / 2, otherPos.z - otherSize.z / 2
    };
    Vector3 BoundingBox2_2 = {
        otherPos.x + otherSize.x / 2, otherPos.y + otherSize.y / 2, otherPos.z + otherSize.z / 2
    };

    BoundingBox BoundingBox1 = { BoundingBox1_1, BoundingBox1_2 };
    BoundingBox BoundingBox2 = { BoundingBox2_1, BoundingBox2_2 };

    return (CheckCollisionBoxes(BoundingBox1, BoundingBox2));
}

Vector3D BoxCollider::getPosition() const noexcept
{
    return (position_);
}

void BoxCollider::setPosition(const Vector3D& pos) noexcept
{
    position_ = pos;
}

void BoxCollider::setPositionZ(int pos) noexcept
{
    position_.z = pos;
}

void BoxCollider::setPositionY(int pos) noexcept
{
    position_.y = pos;
}

void BoxCollider::display() const noexcept
{
    if (debug)
        DrawCubeWiresV(
            { position_.x, position_.y, position_.z }, { size_.x, size_.y, size_.z }, GREEN);
}

void BoxCollider::update(const Vector3D& newPos) noexcept
{
    position_ = newPos;
}

bool BoxCollider::isColliding(const BoxCollider& other) const noexcept
{
    return (checkCollision(position_, size_, other.getPosition(), other.getSize()));
}

bool BoxCollider::isColliding(const BoxCollider& otherHit, const Vector3D& otherPos) const noexcept
{
    return (checkCollision(position_, size_, otherPos, otherHit.getSize()));
}

ComponentType BoxCollider::getComponentType() const noexcept
{
    return (TYPE);
}

Vector3D BoxCollider::getSize() const noexcept
{
    return (size_);
}

void BoxCollider::setIsSolid(bool value) noexcept
{
    is_solid_ = value;
}

bool BoxCollider::getIsSolid() const noexcept
{
    return (is_solid_);
}

void BoxCollider::addX(float value) noexcept
{
    position_.x += value;
}

void BoxCollider::addY(float value) noexcept
{
    position_.y += value;
}

void BoxCollider::addZ(float value) noexcept
{
    position_.z += value;
}
