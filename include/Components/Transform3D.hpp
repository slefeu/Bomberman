/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Transform3D.cpp
*/

#pragma once

#include "raylib.h"

class Transform3D
{
  private:
    Vector3 position;
    Vector3 size;
    float   scale;

  public:
    Transform3D() noexcept;
    Transform3D(Vector3 position, Vector3 size, float scale) noexcept;
    ~Transform3D() noexcept                                 = default;
    Transform3D(const Transform3D& other) noexcept          = delete;
    Transform3D(Transform3D&& other) noexcept               = delete;
    Transform3D& operator=(const Transform3D& rhs) noexcept = delete;
    Transform3D& operator=(Transform3D&& rhs) noexcept      = delete;

    Vector3 getPosition() const noexcept;
    Vector3 getSize() const noexcept;
    float   getScale() const noexcept;
    void    setPosition(Vector3 position) noexcept;
    void    setSize(Vector3 size) noexcept;
    void    setScale(float scale) noexcept;
    void    moveX(float x) noexcept;
    void    moveY(float y) noexcept;
    void    moveZ(float z) noexcept;
    void    setX(float x) noexcept;
    void    setY(float y) noexcept;
    void    setZ(float z) noexcept;
    void    addX(float x) noexcept;
    void    addY(float y) noexcept;
    void    addZ(float z) noexcept;
};