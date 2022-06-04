/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(const std::string& texture_path,
    unsigned int                  frames,
    float                         pos_x,
    float                         pos_y,
    std::function<void(void)>     function,
    float                         scale,
    const std::string&            font_path,
    const std::string&            message,
    int                           textPosX,
    int                           textPosY) noexcept
    : fx_clicked_(ON_CLICK)
    , fx_hover_(ON_HOVER)
    , frames_(frames)
    , task_(function)
    , scale_(scale)
    , text_(font_path, message, textPosX, textPosY)
{
    texture_ = LoadTexture(texture_path.c_str());

    float frameHeight = static_cast<float>(texture_.height) / frames_;
    rectangle_        = { pos_x, pos_y, static_cast<float>(texture_.width), frameHeight };
}

void Button::unload() noexcept
{
    fx_clicked_.unload();
    fx_hover_.unload();
    UnloadTexture(texture_);
    text_.unload();
}

void Button::draw() const noexcept
{
    Vector2 position = { rectangle_.x, rectangle_.y };
    DrawTextureEx(texture_, position, 0, scale_, color_);
    text_.draw();
}

bool Button::checkCollision(const Vector2& mouse_pos) noexcept
{
    if (CheckCollisionPointRec(mouse_pos, rectangle_)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { state_ = 2; }
        if (state_ == 0) {
            state_ = 1;
            color_ = PINK;
            fx_hover_.play();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { is_action_ = true; }
    } else {
        color_ = WHITE;
        state_ = 0;
    }
    if (is_action_) {
        color_ = WHITE;
        fx_clicked_.play();
        is_action_ = false;
        return (true);
    }
    return (false);
}

void Button::action() const noexcept
{
    task_();
}