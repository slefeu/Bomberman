/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Splash
*/

#pragma once

#include <vector>

#include "Color.hpp"
#include "Core.hpp"
#include "Fps.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

class Splash : public Scene
{
  public:
    Splash(Core& core_ref) noexcept;
    Splash(const Splash& other) noexcept          = delete;
    Splash(Splash&& other) noexcept               = delete;
    Splash& operator=(const Splash& rhs) noexcept = delete;
    Splash& operator=(Splash&& rhs) noexcept      = delete;
    ~Splash() noexcept                            = default;

    void display3D() noexcept final;
    void display2D() noexcept final;
    void action() noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;

    void         playMusic() noexcept final;
    void         updateMusic() const noexcept final;
    void         drawBackground() const noexcept final;
    ColorManager getBackgroundColor() const noexcept final;
    void         switchAction() noexcept final;

  private:
    Core&                     core_entry_;
    ColorManager              background_color_;
    Timer                     timer;
    unsigned char             opacity_;
    static const inline char* SPLASH_SCREEN = "assets/audios/MainMenu.mp3";
};
