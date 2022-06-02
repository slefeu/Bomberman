/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#pragma once

#include "Scene.hpp"

class Home : public Scene
{
  public:
    Home(GameData* data) noexcept;
    ~Home() noexcept;
    Home(const Home& other) noexcept = delete;
    Home(Home&& other) noexcept      = delete;
    Home& operator=(const Home& rhs) noexcept = delete;
    Home& operator=(Home&& rhs) noexcept = delete;

    void    resetCamera(Cameraman& camera) noexcept final;
    void    display3D(void) noexcept final;
    void    display2D(void) noexcept final;
    void    action(Cameraman& camera) noexcept final;
    void    DestroyPool() noexcept final;
    void    CollisionPool() noexcept final;
    void    playMusic() const noexcept final;
    Music   getLoopMusic() const noexcept final;
    Vector3 getCameraPosition() const noexcept final;
    Vector3 getCameraTarget() const noexcept final;
    Vector3 getCameraUp() const noexcept final;
    Color   getBackgroundColor() const noexcept final;

  private:
    Music   loop_music_;
    Vector3 camera_position_  = { 20.0f, 50.0f, 20.0f };
    Vector3 camera_target_    = { 0.0f, 0.0f, 0.0f };
    Vector3 camera_up_        = { 0.0f, 1.0f, 0.0f };
    Color   background_color_ = RAYWHITE;
};
