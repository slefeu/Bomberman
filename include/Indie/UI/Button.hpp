/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Button
*/

#pragma once

#include <functional>
#include <string>

#include "Color.hpp"
#include "Mouse.hpp"
#include "Rectangle.hpp"
#include "Sound.hpp"
#include "Sprite.hpp"
#include "Text.hpp"

class Button
{
  public:
    Button() noexcept = delete;
    Button(const std::string&     texture_path,
        unsigned int              frames,
        float                     pos_x,
        float                     pos_y,
        std::function<void(void)> function,
        float                     scale,
        const std::string&        font_path,
        const std::string&        message,
        int                       textPosX,
        int                       textPosY) noexcept;
    Button(const Button& other) noexcept = default;
    Button(Button&& other) noexcept      = default;
    ~Button() noexcept                   = default;

    Button& operator=(const Button& rhs) noexcept = default;
    Button& operator=(Button&& rhs) noexcept = default;

    void draw() const noexcept;
    void unload() noexcept;
    void action() const noexcept;
    bool checkCollision(MouseHandler& mouse_) noexcept;

  protected:
  private:
    SoundManager              fx_clicked_;
    SoundManager              fx_hover_;
    Sprite                    texture_;
    int                       state_     = 0;
    bool                      is_action_ = false;
    unsigned int              frames_;
    RectangleManager          rectangle_;
    std::function<void(void)> task_;
    TextHandler               text_;
    ColorManager              color_;

    static const inline char* ON_CLICK = "assets/audios/OnClick.wav";
    static const inline char* ON_HOVER = "assets/audios/MenuHover.wav";
};
