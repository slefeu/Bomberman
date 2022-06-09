/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Cameraman
*/

#pragma once

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "Vector.hpp"
#include "raylib.h"

class Cameraman
{
  public:
    Cameraman() noexcept;
    ~Cameraman() noexcept                      = default;
    Cameraman(const Cameraman& other) noexcept = delete;
    Cameraman(Cameraman&& other) noexcept      = delete;
    Cameraman& operator=(const Cameraman& rhs) noexcept = delete;
    Cameraman& operator=(Cameraman&& rhs) noexcept = delete;

    Vector3D getPosition() const noexcept;
    Vector3D getTarget() const noexcept;
    Vector3D getUp() const noexcept;
    bool     getIsMoving() const noexcept;
    void     setPosition(const Vector3D& pos) noexcept;
    void     setIsMoving(const bool& isMoving) noexcept;

    void begin3D() const noexcept;
    void moveTo(const Vector3D& to, const Vector3D& target, const Vector3D& up) noexcept;
    void tpTo(const Vector3D& to, const Vector3D& target, const Vector3D& up) noexcept;
    bool smoothMove() noexcept;
    void lookBetweenEntity(std::vector<std::unique_ptr<Entity>>& Entity);

  private:
    Camera3D camera;
    bool     isMoving;
    float    speed;
    Vector3D targetPosition;
    Vector3D targetTarget;
    Vector3D targetUp;

    // methods
    void moveX(const float& x) noexcept;
    void moveY(const float& y) noexcept;
    void moveZ(const float& z) noexcept;
};
