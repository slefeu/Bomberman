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

    void moveX(const float& x) noexcept;
    void moveY(const float& y) noexcept;
    void moveZ(const float& z) noexcept;
    void moveTo(const Vector3& to, const Vector3& target, const Vector3& up) noexcept;
    void tpTo(const Vector3& to, const Vector3& target, const Vector3& up) noexcept;
    bool smoothMove(void) noexcept;
    void lookBetweenEntity(std::vector<std::unique_ptr<Entity>>& Entity);

    Vector3  getPosition() const noexcept;
    Vector3  getTarget() const noexcept;
    Vector3  getUp() const noexcept;
    bool     getIsMoving() const noexcept;
    float    getSpeed() const noexcept;
    Camera3D getCamera() const noexcept;

    void setPosition(const Vector3& pos) noexcept;
    void setTarget(const Vector3& tar) noexcept;
    void setUp(const Vector3& up) noexcept;
    void setIsMoving(const bool& isMoving) noexcept;
    void setSpeed(const float& speed) noexcept;

  private:
    Camera3D camera;
    bool     isMoving;
    float    speed;
    Vector3  targetPosition;
    Vector3  targetTarget;
    Vector3  targetUp;
};
