/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** PlayerSelect
*/

#pragma once

#include <string>

#include "Button.hpp"
#include "Controller.hpp"
#include "Core.hpp"
#include "Entity.hpp"
#include "Fps.hpp"
#include "GameData.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
#include "Text.hpp"

class PlayerSelect : public Scene
{
  public:
    PlayerSelect(Core& core_ref) noexcept;
    PlayerSelect(const PlayerSelect& other) noexcept = delete;
    PlayerSelect(PlayerSelect&& other) noexcept      = delete;
    ~PlayerSelect() noexcept                         = default;

    PlayerSelect& operator=(const PlayerSelect& rhs) noexcept = delete;
    PlayerSelect& operator=(PlayerSelect&& rhs) noexcept      = delete;

    // main methods
    void display3D() noexcept final;
    void display2D() noexcept final;
    void action() noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;
    void switchAction() noexcept final;

    // music methods
    void playMusic() noexcept final;
    void updateMusic() const noexcept final;

    // background methods
    void         drawBackground() const noexcept final;
    ColorManager getBackgroundColor() const noexcept final;

  protected:
  private:
    // methods
    void createButtons() noexcept;
    void drawButtons() const noexcept;
    void displayPlayerStats(const Vector2& stats_pos, const Vector2& texts_pos, int id) noexcept;
    void displayAllStats() noexcept;
    unsigned int findStatsId(const PlayerType& type) const noexcept;
    void drawSelection(const int id, const Vector2& pos_left, const Vector2& pos_right) noexcept;

    // attributes
    MusicManager             loop_music_;
    Core&                    core_entry_;
    ColorManager             background_color_;
    Sprite                   background_;
    Sprite                   title_;
    TextHandler              choose_text_;
    std::vector<Button>      buttons_      = {};
    std::vector<Button>      select_left_  = {};
    std::vector<Button>      select_right_ = {};
    std::vector<Sprite>      stats_        = {};
    std::vector<TextHandler> texts_        = {};
    Controller               controller;
    int                      button_index_ = 0;

    static const inline char*       MUSIC      = "assets/audios/Select.mp3";
    static const inline char*       BG_PATH    = "assets/textures/home/background.png";
    static const inline char*       TITLE_PATH = "assets/textures/selection/title.png";
    static const inline std::string SELECT     = "assets/fonts/menu.ttf";
};