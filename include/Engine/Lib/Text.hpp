/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Text
*/

#pragma once
#include "Color.hpp"
#include "Font.hpp"

class TextHandler
{
  public:
    TextHandler(
        const std::string& font_path, const std::string& message, int posX, int posY) noexcept;
    TextHandler(const TextHandler& other) noexcept = default;
    TextHandler(TextHandler&& other) noexcept      = default;
    ~TextHandler() noexcept                        = default;

    TextHandler& operator=(const TextHandler& rhs) noexcept = default;
    TextHandler& operator=(TextHandler&& rhs) noexcept      = default;

    void draw() const noexcept;
    void setTextColor(const std::array<unsigned char, 3>& color) noexcept;
    void setTextSize(int size) noexcept;
    void unload() noexcept;
    void setPosition(int posX, int posY) noexcept;
    void setText(const std::string& message) noexcept;

  protected:
  private:
    FontHandler  font_;
    std::string  message_;
    Vector2      position_;
    ColorManager color_;
};