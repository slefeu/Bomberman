/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Scene
*/

#pragma once

#include "Cameraman.hpp"
#include "GameData.hpp"

class Scene
{
  public:
    Scene(GameData* data) noexcept
        : data(data){};
    virtual ~Scene() noexcept          = default;
    Scene(const Scene& other) noexcept = delete;
    Scene(Scene&& other) noexcept      = delete;
    Scene& operator=(const Scene& rhs) noexcept = delete;
    Scene& operator=(Scene&& rhs) noexcept = delete;

    virtual void    resetCamera(Cameraman& camera) noexcept = 0;
    virtual void    display3D(void) noexcept                = 0;
    virtual void    display2D(void) noexcept                = 0;
    virtual void    action(Cameraman& camera) noexcept      = 0;
    virtual void    DestroyPool() noexcept                  = 0;
    virtual void    CollisionPool() noexcept                = 0;
    virtual void    playMusic() const noexcept              = 0;
    virtual Music   getLoopMusic() const noexcept           = 0;
    virtual Vector3 getCameraPosition() const noexcept      = 0;
    virtual Vector3 getCameraTarget() const noexcept        = 0;
    virtual Vector3 getCameraUp() const noexcept            = 0;
    virtual Color   getBackgroundColor() const noexcept     = 0;

  protected:
    GameData* data;
};
