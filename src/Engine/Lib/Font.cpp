/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Font
*/

#include "Font.hpp"

FontHandler::FontHandler(std::string path) noexcept
{
    font_ = LoadFontEx(path.c_str(), font_size_, 0, 250);
}

Font FontHandler::getFont() const noexcept
{
    return (font_);
}

void FontHandler::unload() noexcept
{
    UnloadFont(font_);
}

int FontHandler::getFontSize() const noexcept
{
    return (font_size_);
}

void FontHandler::setFontSize(int size) noexcept
{
    font_size_ = size;
}
