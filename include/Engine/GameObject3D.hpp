/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameObject3D
*/

#ifndef GAMEOBJECT3D_HPP_
#define GAMEOBJECT3D_HPP_

#include <memory>
#include <vector>

#include "BoxCollider.hpp"
#include "Render3D.hpp"

enum class EntityType { PLAYER, BOX, BOMB, EXPLOSION, CRATE, WALL };

class GameObject3D
{
  protected:
    Vector3 position;
    Vector3 size;
    Color   color;
    float   scale;

  public:
    bool       isEnable = true;
    EntityType type;

    // Components
  public:
    std::unique_ptr<BoxCollider> hitbox = nullptr;
    std::unique_ptr<Render3D>*   model  = nullptr;

  public:
    GameObject3D() noexcept                                                                  = default;
    virtual ~GameObject3D() noexcept                                                         = default;
    virtual void    display() noexcept                                                       = 0;
    virtual void    action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept      = 0;
    virtual Vector3 getPosition() noexcept                                                   = 0;
    virtual Vector3 getSize() noexcept                                                       = 0;
    virtual bool    isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept = 0;
    virtual bool    isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept = 0;
    virtual bool    update() noexcept                                                                                    = 0;

  protected:
    virtual void moveX(float x) noexcept = 0;
    virtual void moveY(float y) noexcept = 0;
    virtual void moveZ(float z) noexcept = 0;
};

#endif /* !GAMEOBJECT3D_HPP_ */
