/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Camera
*/

#ifndef CAMERAMAN_HPP_
#define CAMERAMAN_HPP_

#include "raylib.h"

class Cameraman : public Camera3D
{
  public:
    Cameraman() noexcept;
    ~Cameraman() noexcept = default;
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    bool smoothMove(Vector3 target, float speed) noexcept;

  public:
    bool isMoving;
    Vector3 target;
};

#endif /* !CAMERA_HPP_ */
