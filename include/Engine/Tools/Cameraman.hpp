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
    void moveTo(Vector3 to, Vector3 target, Vector3 up) noexcept;
    void tpTo(Vector3 to, Vector3 target, Vector3 up) noexcept;
    bool smoothMove(void) noexcept;

  public:
    bool isMoving;
    float speed;
    Vector3 targetPosition;
    Vector3 targetTarget;
    Vector3 targetUp;
};

#endif /* !CAMERA_HPP_ */
