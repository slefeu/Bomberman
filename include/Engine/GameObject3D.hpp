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
#include "Shortcuts.hpp"
#include "Transform3D.hpp"

enum class EntityType { E_PLAYER, E_BOX, E_BOMB, E_EXPLOSION, E_CRATE, E_WALL, E_FIRE, E_ITEM };

class GameObject3D
{
  protected:
    Color color;

  public:
    EntityType                   type;
    bool                         isEnable = true;
    Transform3D                  transform3d;
    std::unique_ptr<BoxCollider> hitbox = nullptr;
    std::unique_ptr<Render3D>*   model  = nullptr;

  public:
    GameObject3D() noexcept                                   = default;
    virtual ~GameObject3D() noexcept                          = default;
    GameObject3D(const GameObject3D& other) noexcept          = delete;
    GameObject3D(GameObject3D&& other) noexcept               = delete;
    GameObject3D& operator=(const GameObject3D& rhs) noexcept = delete;
    GameObject3D& operator=(GameObject3D&& rhs) noexcept      = delete;

    virtual void display() noexcept                                                                                   = 0;
    virtual void action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept                                  = 0;
    virtual bool isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept                             = 0;
    virtual bool isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept = 0;
    virtual bool update() noexcept                                                                                    = 0;
    virtual bool update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept                                  = 0;
    virtual void setLifeTime(float const& newLifeTime) noexcept                                                       = 0;
};

#endif /* !GAMEOBJECT3D_HPP_ */
