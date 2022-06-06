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
    , texture_(texture_path)
    , frames_(frames)
    , task_(function)
    , text_(font_path, message, textPosX, textPosY)
    , color_(Colors::C_WHITE)
{
    float frameHeight = static_cast<float>(texture_.getHeight()) / frames_;
    rectangle_        = { pos_x, pos_y, static_cast<float>(texture_.getWidth()), frameHeight };
    texture_.setPos(rectangle_.x, rectangle_.y);
    texture_.setScale(scale);
}

void Button::unload() noexcept
{
    fx_clicked_.unload();
    fx_hover_.unload();
    text_.unload();
    texture_.unload();
}

void Button::draw() const noexcept
{
    texture_.draw(color_.getColor());
    text_.draw();
}

bool Button::checkCollision(const Vector2& mouse_pos) noexcept
{
    if (CheckCollisionPointRec(mouse_pos, rectangle_)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { state_ = 2; }
        if (state_ == 0) {
            state_ = 1;
            color_.setColor(Colors::C_PINK);
            fx_hover_.play();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { is_action_ = true; }
    } else {
        color_.setColor(Colors::C_WHITE);
        state_ = 0;
    }
    if (is_action_) {
        color_.setColor(Colors::C_WHITE);
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

void Button::setState(int state) noexcept
{
    state_ = state;

    if (state_ == 0) {
        color_.setColor(Colors::C_WHITE);
    } else if (state_ == 1) {
        color_.setColor(Colors::C_PINK);
    } else if (state_ == 2) {
        color_.setColor(Colors::C_PINK);
    }
}