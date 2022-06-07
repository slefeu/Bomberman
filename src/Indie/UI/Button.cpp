/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Button
*/

#include "Button.hpp"

Button::Button(const std::string& texture_path,
    float                         pos_x,
    float                         pos_y,
    std::function<void(void)>     function,
    const std::string&            font_path,
    const std::string&            message,
    int                           textPosX,
    int                           textPosY) noexcept
    : fx_clicked_(ON_CLICK)
    , fx_hover_(ON_HOVER)
    , texture_(texture_path)
    , task_(function)
    , text_(font_path, message, 0, 0)
    , color_(Colors::C_WHITE)
    , rectangle_(pos_x,
          pos_y,
          static_cast<float>(texture_.getWidth()),
          static_cast<float>(texture_.getHeight()))
{
    texture_.setPos(rectangle_.getX(), rectangle_.getY());
    text_.setPosition(
        (pos_x + 150 - (message.size() * 35) / 2) + textPosX, (pos_y + 45) + textPosY);
}

Button::Button(const std::string& texture_path,
    float                         pos_x,
    float                         pos_y,
    std::function<void(void)>     function,
    const std::string&            font_path,
    const std::string&            message) noexcept
    : fx_clicked_(ON_CLICK)
    , fx_hover_(ON_HOVER)
    , texture_(texture_path)
    , task_(function)
    , text_(font_path, message, 0, 0)
    , color_(Colors::C_WHITE)
    , rectangle_(pos_x,
          pos_y,
          static_cast<float>(texture_.getWidth()),
          static_cast<float>(texture_.getHeight()))
{
    texture_.setPos(rectangle_.getX(), rectangle_.getY());
    text_.setPosition(pos_x + 150 - (message.size() * 30) / 2, pos_y + 45);
}

Button::Button(const std::string& texture_path,
    float                         pos_x,
    float                         pos_y,
    std::function<void(void)>     function,
    const std::string&            font_path,
    const std::string&            message,
    float                         scale) noexcept
    : fx_clicked_(ON_CLICK)
    , fx_hover_(ON_HOVER)
    , texture_(texture_path)
    , task_(function)
    , text_(font_path, message, 0, 0)
    , color_(Colors::C_WHITE)
    , rectangle_(pos_x,
          pos_y,
          static_cast<float>(texture_.getWidth()),
          static_cast<float>(texture_.getHeight()))
{
    texture_.setPos(rectangle_.getX(), rectangle_.getY());
    text_.setPosition(pos_x + 150 - (message.size() * 30) / 2, pos_y + 45);
    texture_.setScale(scale);
    rectangle_.setWidth(texture_.getWidth() * scale);
    rectangle_.setHeight(texture_.getHeight() * scale);
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

bool Button::checkCollision(MouseHandler& mouse_) noexcept
{
    if (mouse_.isColliding(rectangle_)) {
        if (mouse_.isClicking()) { state_ = 2; };
        if (state_ == 0) {
            state_ = 1;
            color_.setColor(Colors::C_PINK);
            fx_hover_.play();
        }
        if (mouse_.isClicked()) { is_action_ = true; }
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

void Button::setPosition(const Vector2& pos) noexcept
{
    texture_.setPos(pos.x, pos.y);
    rectangle_.setPos(pos.x, pos.y);
}