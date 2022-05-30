/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#include "BoxCollider.hpp"

#include "Collision.hpp"

BoxCollider::BoxCollider(Vector3 newPos, Vector3 newSize, bool solid) noexcept
    : position_(newPos)
    , size_(newSize)
    , is_solid_(solid)
{
}

Vector3 BoxCollider::getPosition() const noexcept
{
    return (position_);
}

void BoxCollider::setPosition(Vector3 pos) noexcept
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

void BoxCollider::display() noexcept
{
    if (debug) DrawCubeWiresV(position_, size_, GREEN);
}

void BoxCollider::update(Vector3 newPos) noexcept
{
    position_ = newPos;
}

bool BoxCollider::isColliding(const BoxCollider& other) noexcept
{
    return Collision().isColliding(
        position_, size_, other.getPosition(), other.getSize());
}

bool BoxCollider::isColliding(
    const BoxCollider& otherHit, Vector3& otherPos) noexcept
{
    return Collision().isColliding(
        position_, size_, otherPos, otherHit.getSize());
}

ComponentType BoxCollider::getComponentType() const noexcept
{
    return (TYPE);
}

Vector3 BoxCollider::getSize() const noexcept
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

void BoxCollider::addX(float x) noexcept
{
    position_.x += x;
}

void BoxCollider::addY(float y) noexcept
{
    position_.y += y;
}

void BoxCollider::addZ(float z) noexcept
{
    position_.z += z;
}