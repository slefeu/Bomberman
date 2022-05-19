/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#ifndef BOXCOLLIDER_HPP_
#define BOXCOLLIDER_HPP_

#include <memory>

#include "raylib.h"

class BoxCollider
{
  private:
    bool debug = false;

  public:
    Vector3 position;
    Vector3 size;
    bool    isSolid;

  public:
    BoxCollider(Vector3 pos, Vector3 size, bool solid) noexcept;
    ~BoxCollider() noexcept = default;
    void display() noexcept;
    void update(Vector3 pos) noexcept;
    bool isColliding(std::unique_ptr<BoxCollider>& other) noexcept;
    bool isColliding(std::unique_ptr<BoxCollider>& otherHit, Vector3& otherPos) noexcept;
};

#endif /* !BOXCOLLIDER_HPP_ */
