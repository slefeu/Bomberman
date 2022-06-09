/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** BoxCollider
*/

#pragma once

#include <memory>

#include "Component.hpp"
#include "Vector.hpp"

class BoxCollider : public Component
{
  public:
    BoxCollider(Vector3D pos, Vector3D size, bool solid) noexcept;
    BoxCollider(const BoxCollider& other) noexcept = default;
    BoxCollider(BoxCollider&& other) noexcept      = default;
    ~BoxCollider() noexcept                        = default;

    BoxCollider& operator=(const BoxCollider& rhs) noexcept = default;
    BoxCollider& operator=(BoxCollider&& rhs) noexcept = default;

    void          display() const noexcept; // pour du débugage
    void          update(Vector3D pos) noexcept;
    bool          isColliding(const BoxCollider& other) noexcept;
    bool          isColliding(const BoxCollider& otherHit, Vector3D& otherPos) noexcept;
    bool          checkCollision(const Vector3D& pos,
                 const Vector3D&                 size,
                 const Vector3D&                 otherPos,
                 const Vector3D&                 otherSize) noexcept;
    Vector3D      getPosition() const noexcept;
    void          setPosition(const Vector3D& pos) noexcept;
    Vector3D      getSize() const noexcept;
    bool          getIsSolid() const noexcept;
    void          setIsSolid(const bool& newValue) noexcept;
    ComponentType getComponentType() const noexcept;
    void          setPositionY(const int& pos) noexcept;
    void          setPositionZ(const int& pos) noexcept;
    void          addX(const float& x) noexcept;
    void          addY(const float& x) noexcept;
    void          addZ(const float& x) noexcept;

    static constexpr ComponentType TYPE = ComponentType::BOXCOLLIDER;

  protected:
  private:
    Vector3D position_;
    Vector3D size_;
    bool     is_solid_;
    bool     debug = true; // pour du débugage
};
