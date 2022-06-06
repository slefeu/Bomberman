/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** PlayerSelect
*/

#pragma once

#include <string>

#include "Button.hpp"
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
    PlayerSelect(GameData* data, Core& core_ref) noexcept;
    PlayerSelect(const PlayerSelect& other) noexcept = delete;
    PlayerSelect(PlayerSelect&& other) noexcept      = delete;
    ~PlayerSelect() noexcept;

    PlayerSelect& operator=(const PlayerSelect& rhs) noexcept = delete;
    PlayerSelect& operator=(PlayerSelect&& rhs) noexcept = delete;

    // main methods
    void display3D() noexcept final;
    void display2D() noexcept final;
    void action(Cameraman& camera, MouseHandler mouse_) noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;
    void switchAction() noexcept final;

    // music methods
    void         playMusic() const noexcept final;
    MusicManager getMusicManager() const noexcept final;

    // camera methods
    Vector3 getCameraPosition() const noexcept final;
    Vector3 getCameraTarget() const noexcept final;
    Vector3 getCameraUp() const noexcept final;
    void    resetCameraman(Cameraman& camera) noexcept;

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
    Vector3                  camera_position_ = { 4.0f, 2.0f, 1.5f };
    Vector3                  camera_target_   = { 0.0f, 1.0f, 1.5f };
    Vector3                  camera_up_       = { 0.0f, 2.0f, 0.0f };
    GameData*                data_;
    Core&                    core_entry_;
    ColorManager             background_color_;
    Sprite                   background_;
    Sprite                   title_;
    TextHandler              choose_;
    std::vector<Button>      buttons_      = {};
    std::vector<Button>      select_left_  = {};
    std::vector<Button>      select_right_ = {};
    std::vector<Sprite>      stats_        = {};
    std::vector<TextHandler> texts_        = {};

    static const inline char*       MUSIC      = "assets/audios/Select.mp3";
    static const inline char*       BG_PATH    = "assets/textures/home/background.png";
    static const inline char*       TITLE_PATH = "assets/textures/selection/title.png";
    static const inline std::string SELECT     = "assets/fonts/menu.ttf";
};