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
    Home(Core& core_ref) noexcept;
    Home(const Home& other) noexcept = delete;
    Home(Home&& other) noexcept      = delete;
    Home& operator=(const Home& rhs) noexcept = delete;
    Home& operator=(Home&& rhs) noexcept = delete;
    ~Home() noexcept                     = default;

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
    // methods
    void drawButtons() const noexcept;
    void createButtons() noexcept;
    void createTexts() noexcept;

    // attributes
    MusicManager             loop_music_;
    std::vector<Button>      buttons_      = {};
    int                      button_index_ = 0;
    Core&                    core_entry_;
    ColorManager             background_color_;
    Sprite                   background_;
    Sprite                   title_;
    Controller               controller;
    std::vector<Button>      settings_;
    std::vector<TextHandler> settings_texts_;

    static const inline char* MENU_MUSIC = "assets/audios/MainMenu.mp3";
    static const inline char* BG_PATH    = "assets/textures/home/background.png";
    static const inline char* TITLE_PATH = "assets/textures/home/title.png";
    static const inline char* FONT_PATH  = "assets/fonts/menu.ttf";
};
