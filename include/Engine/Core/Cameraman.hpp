/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#pragma once

#include <memory>
#include <vector>

#include "Entities.hpp"
#include "raylib.h"

class Cameraman : public Camera3D
{
  public:
    Cameraman() noexcept;
    ~Cameraman() noexcept                               = default;
    Cameraman(const Cameraman& other) noexcept          = delete;
    Cameraman(Cameraman&& other) noexcept               = delete;
    Cameraman& operator=(const Cameraman& rhs) noexcept = delete;
    Cameraman& operator=(Cameraman&& rhs) noexcept      = delete;

    void moveX(const float& x) noexcept;
    void moveY(const float& y) noexcept;
    void moveZ(const float& z) noexcept;
    void moveTo(const Vector3& to, const Vector3& target, const Vector3& up) noexcept;
    void tpTo(const Vector3& to, const Vector3& target, const Vector3& up) noexcept;
    bool smoothMove(void) noexcept;
    void lookBetweenEntities(std::vector<std::unique_ptr<Entities>>& entities);

  public:
    bool    isMoving;
    float   speed;
    Vector3 targetPosition;
    Vector3 targetTarget;
    Vector3 targetUp;
};
