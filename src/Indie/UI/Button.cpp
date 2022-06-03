/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Button
*/

#include "Button.hpp"

#include "Shortcuts.hpp"

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
    : frames_(frames)
    , task_(function)
    , scale_(scale)
    , text_(font_path, message, textPosX, textPosY)
{
    fx_clicked_ = LoadSound(ON_CLICK);
    fx_hover_   = LoadSound(ON_HOVER);
    texture_    = LoadTexture(texture_path.c_str());

    float frameHeight = static_cast<float>(texture_.height) / frames_;
    rectangle_        = {
        pos_x, pos_y, static_cast<float>(texture_.width), frameHeight
    };
}

Texture2D Button::getTexture() const noexcept
{
    return (texture_);
}

Sound Button::getHoverSound() const noexcept
{
    return (fx_hover_);
}

Sound Button::getClickedSound() const noexcept
{
    return (fx_clicked_);
}

void Button::unload() noexcept
{
    UnloadSound(fx_clicked_);
    UnloadSound(fx_hover_);
    UnloadTexture(texture_);
    text_.unload();
}

void Button::draw() const noexcept
{
    if (scale_ != 1) {
        Vector2 position = { rectangle_.x, rectangle_.y };
        DrawTextureEx(texture_, position, 0, scale_, WHITE);
    } else
        DrawTexture(texture_, rectangle_.x, rectangle_.y, WHITE);
    text_.draw();
}

bool Button::checkCollision(const Vector2& mouse_pos) noexcept
{
    if (CheckCollisionPointRec(mouse_pos, rectangle_)) {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) { state_ = 2; }
        if (state_ == 0) {
            state_ = 1;
            PlaySound(fx_hover_);
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) { is_action_ = true; }
    } else
        state_ = 0;
    if (is_action_) {
        PlaySound(fx_clicked_);
        is_action_ = false;
        return (true);
    }
    return (false);
}

void Button::setButtonAction(bool value) noexcept
{
    is_action_ = value;
}

void Button::action() const noexcept
{
    task_();
}