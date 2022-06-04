/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

BoxCollider::BoxCollider(Vector3 newPos, Vector3 newSize, bool solid) noexcept
    : position_(newPos)
    , size_(newSize)
    , is_solid_(solid)
{
}

bool BoxCollider::checkCollision(const Vector3& pos,
    const Vector3&                              size,
    const Vector3&                              otherPos,
    const Vector3&                              otherSize) noexcept
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

    return CheckCollisionBoxes(BoundingBox1, BoundingBox2);
}

Vector3 BoxCollider::getPosition() const noexcept
{
    return (position_);
}

void BoxCollider::setPosition(const Vector3& pos) noexcept
{
    position_ = pos;
}

void BoxCollider::setPositionZ(const int& pos) noexcept
{
    position_.z = pos;
}

void BoxCollider::setPositionY(const int& pos) noexcept
{
    position_.y = pos;
}

void BoxCollider::display() const noexcept
{
    if (debug) DrawCubeWiresV(position_, size_, GREEN);
}

void BoxCollider::update(const Vector3 newPos) noexcept
{
    position_ = newPos;
}

bool BoxCollider::isColliding(const BoxCollider& other) noexcept
{
    return checkCollision(position_, size_, other.getPosition(), other.getSize());
}

bool BoxCollider::isColliding(const BoxCollider& otherHit, Vector3& otherPos) noexcept
{
    return checkCollision(position_, size_, otherPos, otherHit.getSize());
}

ComponentType BoxCollider::getComponentType() const noexcept
{
    return (TYPE);
}

Vector3 BoxCollider::getSize() const noexcept
{
    return (size_);
}

void BoxCollider::setIsSolid(const bool& value) noexcept
{
    is_solid_ = value;
}

bool BoxCollider::getIsSolid() const noexcept
{
    return (is_solid_);
}

void BoxCollider::addX(const float& x) noexcept
{
    position_.x += x;
}

void BoxCollider::addY(const float& y) noexcept
{
    position_.y += y;
}

void BoxCollider::addZ(const float& z) noexcept
{
    position_.z += z;
}
