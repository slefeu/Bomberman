/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** HitBox
*/

#ifndef HITBOX_HPP_
#define HITBOX_HPP_

#include <memory>

#include "raylib.h"

class HitBox
{
  public:
    Vector3 position;
    Vector3 size;
    bool    isSolid;

  public:
    HitBox(Vector3 pos, Vector3 size, bool solid) noexcept;
    ~HitBox() noexcept = default;
    void display() noexcept;
    void update(Vector3 pos) noexcept;
    bool isColliding(std::unique_ptr<HitBox>& other) noexcept;
    bool isColliding(std::unique_ptr<HitBox>& otherHit, Vector3& otherPos) noexcept;
};

#endif /* !HITBOX_HPP_ */
