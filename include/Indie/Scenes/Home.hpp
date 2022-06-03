/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#pragma once

#include <vector>

#include "Button.hpp"
#include "Core.hpp"
#include "Scene.hpp"

static const inline char* MENU_MUSIC = "assets/audios/Menu.mp3";

class Home : public Scene
{
  public:
    Home(GameData* data, Core& core_ref) noexcept;
    ~Home() noexcept;
    Home(const Home& other) noexcept = delete;
    Home(Home&& other) noexcept      = delete;
    Home& operator=(const Home& rhs) noexcept = delete;
    Home& operator=(Home&& rhs) noexcept = delete;

    void    resetCamera(Cameraman& camera) noexcept final;
    void    display3D(void) noexcept final;
    void    display2D(void) noexcept final;
    void    action(Cameraman& camera, Vector2 mouse_pos) noexcept final;
    void    DestroyPool() noexcept final;
    void    CollisionPool() noexcept final;
    void    playMusic() const noexcept final;
    Music   getLoopMusic() const noexcept final;
    Vector3 getCameraPosition() const noexcept final;
    Vector3 getCameraTarget() const noexcept final;
    Vector3 getCameraUp() const noexcept final;
    Color   getBackgroundColor() const noexcept final;
    void    setButtons() noexcept final;
    void    drawBackground() const noexcept final;

  private:
    // methods
    void unloadTextures() noexcept;
    void unloadButtons() noexcept;
    void drawButtons() const noexcept;
    void createButtons() noexcept;

    // attributes
    Music               loop_music_;
    Vector3             camera_position_  = { 20.0f, 50.0f, 20.0f };
    Vector3             camera_target_    = { 0.0f, 0.0f, 0.0f };
    Vector3             camera_up_        = { 0.0f, 1.0f, 0.0f };
    Color               background_color_ = RAYWHITE;
    std::vector<Button> buttons_          = {};
    GameData*           data_;
    Core&               core_entry_;

    // a faire : classe pour handle un background
    Texture2D texture;
    Texture2D title;
};
