/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Scene
*/

#pragma once

#include "Cameraman.hpp"
#include "Music.hpp"

enum class SceneType : std::size_t { MENU, GAME };

class Scene
{
  public:
    Scene() noexcept                            = default;
    virtual ~Scene() noexcept                   = default;
    Scene(const Scene& other) noexcept          = delete;
    Scene(Scene&& other) noexcept               = delete;
    Scene& operator=(const Scene& rhs) noexcept = delete;
    Scene& operator=(Scene&& rhs) noexcept      = delete;

    virtual void  action(Cameraman& camera, Vector2 mouse_pos) noexcept = 0;
    virtual void  DestroyPool() noexcept                                = 0;
    virtual void  CollisionPool() noexcept                              = 0;
    virtual Color getBackgroundColor() const noexcept                   = 0;
    virtual void  drawBackground() const noexcept                       = 0;

    // methods for camera
    virtual void    resetCameraman(Cameraman& camera) noexcept = 0;
    virtual Vector3 getCameraPosition() const noexcept         = 0;
    virtual Vector3 getCameraTarget() const noexcept           = 0;
    virtual Vector3 getCameraUp() const noexcept               = 0;

    // methods for musics
    virtual void         playMusic() const noexcept       = 0;
    virtual MusicManager getMusicManager() const noexcept = 0;

    // methods for display
    virtual void display3D(void) noexcept = 0;
    virtual void display2D(void) noexcept = 0;
};
