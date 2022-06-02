/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Transform3D.cpp
*/

#pragma once

#include "Component.hpp"
#include "raylib.h"

class Transform3D : public Component
{
  public:
    Transform3D() noexcept;
    ~Transform3D() noexcept                                 = default;
    Transform3D(const Transform3D& other) noexcept          = default;
    Transform3D(Transform3D&& other) noexcept               = default;
    Transform3D& operator=(const Transform3D& rhs) noexcept = default;
    Transform3D& operator=(Transform3D&& rhs) noexcept      = default;

    Vector3 getPosition() const noexcept;
    Vector3 getSize() const noexcept;
    float   getScale() const noexcept;
    Vector3 getRotationAxis() const noexcept;
    float   getRotationAngle() const noexcept;
    void    setPosition(const Vector3& position) noexcept;
    void    setSize(const Vector3& size) noexcept;
    void    setScale(float scale) noexcept;
    void    setRotationAxis(const Vector3& rotationAxis) noexcept;
    void    setRotationAngle(float rotationAngle) noexcept;
    void    moveX(const float& x) noexcept;
    void    moveY(const float& y) noexcept;
    void    moveZ(const float& z) noexcept;
    void    setX(const float& x) noexcept;
    void    setY(const float& y) noexcept;
    void    setZ(const float& z) noexcept;
    void    addX(const float& x) noexcept;
    void    addY(const float& y) noexcept;
    void    addZ(const float& z) noexcept;
    float   getPositionX() const noexcept;
    float   getPositionY() const noexcept;
    float   getPositionZ() const noexcept;

    ComponentType getComponentType() const noexcept;

    static constexpr ComponentType TYPE = ComponentType::TRANSFORM;

  private:
    Vector3 position;
    Vector3 size;
    float   scale;
    Vector3 rotationAxis;
    float   rotationAngle;
};
