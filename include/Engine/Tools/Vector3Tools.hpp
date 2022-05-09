/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Vector3Tools
*/

#ifndef VECTOR3TOOLS_HPP_
#define VECTOR3TOOLS_HPP_

#include "raylib.h"

class Vector3Tools
{
  public:
    Vector3Tools() noexcept = default;
    ~Vector3Tools() noexcept = default;
    Vector3 add(Vector3 v1, Vector3 v2) noexcept;
    Vector3 sub(Vector3 v1, Vector3 v2) noexcept;
    Vector3 mul(Vector3 v1, Vector3 v2) noexcept;
    Vector3 div(Vector3 v1, Vector3 v2) noexcept;
    Vector3 add(Vector3 v1, float v2) noexcept;
    Vector3 sub(Vector3 v1, float v2) noexcept;
    Vector3 mul(Vector3 v1, float v2) noexcept;
    Vector3 div(Vector3 v1, float v2) noexcept;
    bool equals(Vector3 v1, Vector3 v2) noexcept;

  protected:
  private:
};

#endif /* !VECTOR3TOOLS_HPP_ */
