/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Entities
*/

#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include "raylib.h"

class Entities
{
  public:
    Entities() noexcept                     = default;
    virtual ~Entities() noexcept            = default;
    virtual void    display() noexcept      = 0;
    virtual void    moveX(float x) noexcept = 0;
    virtual void    moveY(float y) noexcept = 0;
    virtual void    moveZ(float z) noexcept = 0;
    virtual void    action(void) noexcept   = 0;
    virtual Vector3 getPosition() noexcept  = 0;

  protected:
    Vector3 position;
    Vector3 size;
    Color   color;
};

#endif /* !ENTITIES_HPP_ */
