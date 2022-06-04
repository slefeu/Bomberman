/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Text
*/

#include "Text.hpp"

TextHandler::TextHandler(const std::string& font_path,
    const std::string&                      message,
    int                                     posX,
    int                                     posY) noexcept
    : font_(font_path)
    , message_(message)
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
    DrawTextEx(font_.getFont(),
        message_.c_str(),
        position_,
        font_.getFontSize(),
        0,
        color_);
}

void TextHandler::setTextColor(Color color) noexcept
{
    color_ = color;
}

void TextHandler::setTextSize(int size) noexcept
{
    font_.setFontSize(size);
}
