/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Transform3D
*/

#include "Transform3D.hpp"

Transform3D::Transform3D() noexcept
    : position({ 0.0f, 0.0f, 0.0f })
    , size({ 1.0f, 1.0f, 1.0f })
    , scale(1.0f)
{
}

ComponentType Transform3D::getComponentType() const noexcept
{
    return (TYPE);
}

Vector3 Transform3D::getPosition() const noexcept
{
    return position;
}

float Transform3D::getPositionX() const noexcept
{
    return position.x;
}

float Transform3D::getPositionY() const noexcept
{
    return position.y;
}

float Transform3D::getPositionZ() const noexcept
{
    return position.z;
}

Vector3 Transform3D::getSize() const noexcept
{
    return size;
}

float Transform3D::getScale() const noexcept
{
    return scale;
}

Vector3 Transform3D::getRotationAxis() const noexcept
{
    return rotationAxis;
}

float Transform3D::getRotationAngle() const noexcept
{
    return rotationAngle;
}

void Transform3D::setPosition(const Vector3& position) noexcept
{
    this->position = position;
}

void Transform3D::setSize(const Vector3& size) noexcept
{
    this->size = size;
}

void Transform3D::setScale(float scale) noexcept
{
    this->scale = scale;
}

void Transform3D::setRotationAxis(const Vector3& rotationAxis) noexcept
{
    this->rotationAxis = rotationAxis;
}

void Transform3D::setRotationAngle(float rotationAngle) noexcept
{
    this->rotationAngle = rotationAngle;
}

void Transform3D::moveX(const float& x) noexcept
{
    position.x += x * GetFrameTime();
}

void Transform3D::moveY(const float& y) noexcept
{
    position.y += y * GetFrameTime();
}

void Transform3D::moveZ(const float& z) noexcept
{
    position.z += z * GetFrameTime();
}

void Transform3D::setX(const float& x) noexcept
{
    position.x = x;
}

void Transform3D::setY(const float& y) noexcept
{
    position.y = y;
}

void Transform3D::setZ(const float& z) noexcept
{
    position.z = z;
}

void Transform3D::addX(const float& x) noexcept
{
    position.x += x;
}

void Transform3D::addY(const float& y) noexcept
{
    position.y += y;
}

void Transform3D::addZ(const float& z) noexcept
{
    position.z += z;
}
