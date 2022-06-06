/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Text
*/

#include "Text.hpp"

TextHandler::TextHandler(
    const std::string& font_path, const std::string& message, int posX, int posY) noexcept
    : font_(font_path)
    , message_(message)
    , color_(Colors::C_WHITE)
{
    position_.x = posX;
    position_.y = posY;
}

void TextHandler::unload() noexcept
{
    font_.unload();
}

void TextHandler::draw() const noexcept
{
    auto color = color_.getColor();

    DrawTextEx(font_.getFont(),
        message_.c_str(),
        position_,
        font_.getFontSize(),
        0,
        (Color){ color[0], color[1], color[2], 255 });
}

void TextHandler::setTextColor(const std::array<unsigned char, 3>& color) noexcept
{
    color_.setColor(color);
}

void TextHandler::setTextSize(int size) noexcept
{
    font_.setFontSize(size);
}

void TextHandler::setPosition(int posX, int posY) noexcept
{
    position_.x = posX;
    position_.y = posY;
}