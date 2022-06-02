/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Button
*/

#pragma once

#include <string>

#include "raylib.h"

static const inline char* ON_CLICK = "assets/audios/Btn_clicked.ogg";
static const inline char* ON_HOVER = "assets/audios/menu_hover.ogg";

class Button
{
  public:
    Button() noexcept = delete;
    Button(const std::string& texture_path,
        unsigned int          frames,
        float                 pos_x,
        float                 pos_y) noexcept;
    Button(const Button& other) noexcept = default;
    Button(Button&& other) noexcept      = default;
    ~Button() noexcept                   = default;

    Button& operator=(const Button& rhs) noexcept = default;
    Button& operator=(Button&& rhs) noexcept = default;

    Texture2D getTexture() const noexcept;
    Sound     getHoverSound() const noexcept;
    Sound     getClickedSound() const noexcept;
    void      draw() const noexcept;
    bool      checkCollision(const Vector2& mouse_pos) noexcept;
    void      unload() noexcept;
    void      setButtonAction(bool value) noexcept;

  protected:
  private:
    Sound        fx_clicked_;
    Sound        fx_hover_;
    Texture2D    texture_;
    int          state_     = 0; // 0 : NORMAL, 1 : HOVER, 2 : PRESSED
    bool         is_action_ = false;
    unsigned int nb_frames_;
    Rectangle    rectangle_;
};