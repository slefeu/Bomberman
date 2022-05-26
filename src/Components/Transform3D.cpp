#include "Transform3D.hpp"

Transform3D::Transform3D() noexcept
    : position({ 0.0f, 0.0f, 0.0f })
    , size({ 1.0f, 1.0f, 1.0f })
    , scale(1.0f)
{
}

Transform3D::Transform3D(Vector3 position, Vector3 size, float scale) noexcept
    : position(position)
    , size(size)
    , scale(scale)
{
}

Vector3 Transform3D::getPosition() const noexcept
{
    return position;
}

Vector3 Transform3D::getSize() const noexcept
{
    return size;
}

float Transform3D::getScale() const noexcept
{
    return scale;
}

void Transform3D::setPosition(Vector3 position) noexcept
{
    this->position = position;
}

void Transform3D::setSize(Vector3 size) noexcept
{
    this->size = size;
}

void Transform3D::setScale(float scale) noexcept
{
    this->scale = scale;
}

void Transform3D::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Transform3D::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Transform3D::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

void Transform3D::setX(float x) noexcept
{
    position.x = x;
}

void Transform3D::setY(float y) noexcept
{
    position.y = y;
}

void Transform3D::setZ(float z) noexcept
{
    position.z = z;
}

void Transform3D::addX(float x) noexcept
{
    position.x += x;
}

void Transform3D::addY(float y) noexcept
{
    position.y += y;
}

void Transform3D::addZ(float z) noexcept
{
    position.z += z;
}