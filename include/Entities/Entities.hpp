/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Entities
*/

#ifndef ENTITIES_HPP_
#define ENTITIES_HPP_

#include <memory>
#include <vector>

#include "HitBox.hpp"

enum class EntityType { PLAYER, BOX, BOMB, EXPLOSION, CRATE, WALL };

class Entities
{
  protected:
    Vector3 position;
    Vector3 size;
    Color   color;

  protected:
    Model     model;
    Texture2D texture;
    float     scale;

  public:
    EntityType              type;
    bool                    isEnable;
    std::unique_ptr<HitBox> hitbox;

  public:
    Entities() noexcept                                                                                              = default;
    virtual ~Entities() noexcept                                                                                     = default;
    virtual void    display() noexcept                                                                               = 0;
    virtual void    action(std::vector<std::unique_ptr<Entities>>& others) noexcept                                  = 0;
    virtual Vector3 getPosition() noexcept                                                                           = 0;
    virtual Vector3 getSize() noexcept                                                                               = 0;
    virtual bool    isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept                             = 0;
    virtual bool    isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept = 0;
    virtual bool    update() noexcept                                                                                = 0;

  protected:
    virtual void moveX(float x) noexcept = 0;
    virtual void moveY(float y) noexcept = 0;
    virtual void moveZ(float z) noexcept = 0;
};

#endif /* !ENTITIES_HPP_ */
