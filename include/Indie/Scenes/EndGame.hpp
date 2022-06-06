/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** EndGame
*/

#pragma once

#include <vector>

#include "Button.hpp"
#include "Controller.hpp"
#include "Core.hpp"
#include "Fps.hpp"
#include "Scene.hpp"

class EndGame : public Scene
{
  public:
    EndGame(GameData* data, Core& core_ref) noexcept;
    EndGame(const EndGame& other) noexcept          = delete;
    EndGame(EndGame&& other) noexcept               = delete;
    EndGame& operator=(const EndGame& rhs) noexcept = delete;
    EndGame& operator=(EndGame&& rhs) noexcept      = delete;
    ~EndGame() noexcept;

    void display3D() noexcept final;
    void display2D() noexcept final;
    void action(Cameraman& camera, Vector2 mouse_pos) noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;

    void createButtons() noexcept;
    void drawButtons() const noexcept;
    void unloadButtons() noexcept;

    void         playMusic() noexcept final;
    MusicManager getMusicManager() const noexcept final;
    Vector3      getCameraPosition() const noexcept final;
    Vector3      getCameraTarget() const noexcept final;
    Vector3      getCameraUp() const noexcept final;
    void         drawBackground() const noexcept final{};
    void         resetCameraman(Cameraman& camera) noexcept;
    ColorManager getBackgroundColor() const noexcept final;

  private:
    // attributes
    Vector3             camera_position_ = { 0.0f, 1.0f, 2.0f };
    Vector3             camera_target_   = { 0.0f, 1.0f, 0.0f };
    Vector3             camera_up_       = { 0.0f, 2.0f, 0.0f };
    std::vector<Button> buttons_         = {};
    GameData*           data_;
    Core&               core_entry_;
    ColorManager        background_color_;
    Controller          controller;
    MusicManager        victory_music_;
    bool                isEnd         = false;
    int                 button_index_ = 0;

    static const inline char* VICTORY_MUSIC = "assets/audios/Victory.mp3";
};
