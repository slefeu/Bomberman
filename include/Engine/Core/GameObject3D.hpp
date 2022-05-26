/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameObject3D
*/

#pragma once

#include <memory>
#include <vector>

#include "BoxCollider.hpp"
#include "Model3D.hpp"
#include "Render.hpp"
#include "Shortcuts.hpp"
#include "Transform3D.hpp"

class GameObject3D
{
  public:
    EntityType                   type;
    bool                         isEnable = true;
    Transform3D                  transform3d;
    Render                       render;
    std::unique_ptr<BoxCollider> hitbox = nullptr;
    std::unique_ptr<Model3D>*    model  = nullptr;

  public:
    GameObject3D() noexcept                                   = default;
    virtual ~GameObject3D() noexcept                          = default;
    GameObject3D(const GameObject3D& other) noexcept          = delete;
    GameObject3D(GameObject3D&& other) noexcept               = delete;
    GameObject3D& operator=(const GameObject3D& rhs) noexcept = delete;
    GameObject3D& operator=(GameObject3D&& rhs) noexcept      = delete;

    virtual void Display() noexcept                                              = 0;
    virtual void Update() noexcept                                               = 0;
    virtual void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept = 0;
};
