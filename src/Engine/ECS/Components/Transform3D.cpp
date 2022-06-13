/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Transform3D
*/

#include "Transform3D.hpp"

#include "DeltaTime.hpp"

ComponentType Transform3D::getComponentType() const noexcept
{
    return (TYPE);
}

Vector3D Transform3D::getPosition() const noexcept
{
    return (position_);
}

float Transform3D::getPositionX() const noexcept
{
    return (position_.x);
}

float Transform3D::getPositionY() const noexcept
{
    return (position_.y);
}

float Transform3D::getPositionZ() const noexcept
{
    return (position_.z);
}

float Transform3D::getScale() const noexcept
{
    return (scale_);
}

Vector3D Transform3D::getRotationAxis() const noexcept
{
    return (rotation_axis_);
}

float Transform3D::getRotationAngle() const noexcept
{
    return (rotation_angle_);
}

void Transform3D::setPosition(const Vector3D& position) noexcept
{
    position_ = position;
}

void Transform3D::setScale(float scale) noexcept
{
    scale_ = scale;
}

void Transform3D::setRotationAxis(const Vector3D& rotation_axis) noexcept
{
    rotation_axis_ = rotation_axis;
}

void Transform3D::setRotationAngle(float angle) noexcept
{
    rotation_angle_ = angle;
}

void Transform3D::moveX(float x) noexcept
{
    position_.x += x * DeltaTime::getDeltaTime();
}

void Transform3D::moveY(float y) noexcept
{
    position_.y += y * DeltaTime::getDeltaTime();
}

void Transform3D::moveZ(float z) noexcept
{
    position_.z += z * DeltaTime::getDeltaTime();
}

void Transform3D::setX(float x) noexcept
{
    position_.x = x;
}

void Transform3D::setY(float y) noexcept
{
    position_.y = y;
}

void Transform3D::setZ(float z) noexcept
{
    position_.z = z;
}

void Transform3D::addX(float x) noexcept
{
    position_.x += x;
}

void Transform3D::addY(float y) noexcept
{
    position_.y += y;
}

void Transform3D::addZ(float z) noexcept
{
    position_.z += z;
}
