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
    ~Home() noexcept                          = default;
    Home(const Home& other) noexcept          = delete;
    Home(Home&& other) noexcept               = delete;
    Home& operator=(const Home& rhs) noexcept = delete;
    Home& operator=(Home&& rhs) noexcept      = delete;

    void resetCameraman(Cameraman& camera) noexcept;
    void display3D(void) noexcept;
    void display2D(void) noexcept;
    void action(Cameraman& camera) noexcept;
    void DestroyPool() noexcept;
    void CollisionPool() noexcept;
};
