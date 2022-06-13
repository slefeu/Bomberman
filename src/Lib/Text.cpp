/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Text
*/

#include "Text.hpp"

TextHandler::TextHandler(
    const std::string_view& font_path, const std::string_view& message, int posX, int posY) noexcept
    : font_(LoadFontEx(font_path.data(), font_size_, 0, 250))
    , message_(message.data())
    , color_(Colors::C_WHITE)
{
    setPosition(posX, posY);
}

TextHandler::TextHandler(TextHandler&& other) noexcept
    : font_(std::move(other.font_))
    , message_(other.message_)
    , position_(other.position_)
    , color_(other.color_)
{
    other.unloaded_ = true;
}

TextHandler& TextHandler::operator=(TextHandler&& rhs) noexcept
{
    font_         = std::move(rhs.font_);
    message_      = rhs.message_;
    position_     = rhs.position_;
    color_        = rhs.color_;
    rhs.unloaded_ = true;
    return *(this);
}

TextHandler::~TextHandler() noexcept
{
    this->unload();
}

void TextHandler::unload() noexcept
{
    if (!unloaded_) {
        UnloadFont(font_);
        unloaded_ = true;
    }
}
void TextHandler::draw() const noexcept
{
    auto color = color_.getColor();
    Color col   = { color[0], color[1], color[2], 255 };

    if (!displayed_) { return; }
    DrawTextEx(font_,
        message_.c_str(),
        { position_.x, position_.y },
        font_size_,
        0,
        col);
}

void TextHandler::invertDisplay() noexcept
{
    displayed_ = !displayed_;
}

void TextHandler::setTextColor(const std::array<unsigned char, 3>& color) noexcept
{
    color_.setColor(color);
}

void TextHandler::setTextSize(int size) noexcept
{
    font_size_ = size;
}

void TextHandler::setPosition(int posX, int posY) noexcept
{
    position_.x = posX;
    position_.y = posY;
}

void TextHandler::setText(const std::string_view& message) noexcept
{
    message_ = message;
}

std::string& TextHandler::getText() noexcept
{
    return message_;
}
