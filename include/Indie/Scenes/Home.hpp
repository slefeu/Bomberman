/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#pragma once

#include <vector>

#include "Button.hpp"
#include "Controller.hpp"
#include "Core.hpp"
#include "Fps.hpp"
#include "Scene.hpp"

class Home : public Scene
{
  public:
    Home(GameData* data, Core& core_ref) noexcept;
    Home(const Home& other) noexcept          = delete;
    Home(Home&& other) noexcept               = delete;
    Home& operator=(const Home& rhs) noexcept = delete;
    Home& operator=(Home&& rhs) noexcept      = delete;
    ~Home() noexcept;

    void display3D() noexcept final;
    void display2D() noexcept final;
    void action(Cameraman& camera, MouseHandler mouse_) noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;

    void         playMusic() noexcept final;
    MusicManager getMusicManager() const noexcept final;
    Vector3D     getCameraPosition() const noexcept final;
    Vector3D     getCameraTarget() const noexcept final;
    Vector3D     getCameraUp() const noexcept final;
    void         drawBackground() const noexcept final;
    void         resetCameraman(Cameraman& camera) noexcept;
    ColorManager getBackgroundColor() const noexcept final;
    void         switchAction() noexcept final;

  private:
    // methods
    void unloadButtons() noexcept;
    void drawButtons() const noexcept;
    void createButtons() noexcept;

    // attributes
    MusicManager        loop_music_;
    Vector3D            camera_position_ = { 20.0f, 50.0f, 30.0f };
    Vector3D            camera_target_   = { 0.0f, 0.0f, 1.0f };
    Vector3D            camera_up_       = { 0.0f, 2.0f, 0.0f };
    std::vector<Button> buttons_         = {};
    int                 button_index_    = 0;
    GameData*           data_;
    Core&               core_entry_;
    ColorManager        background_color_;
    Sprite              background_;
    Sprite              title_;
    Controller          controller;

    static const inline char* MENU_MUSIC = "assets/audios/MainMenu.mp3";
    static const inline char* BG_PATH    = "assets/textures/home/background.png";
    static const inline char* TITLE_PATH = "assets/textures/home/title.png";
};
