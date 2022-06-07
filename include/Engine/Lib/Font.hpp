/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Font
*/

#pragma once
#include <string>

#include "raylib.h"
class FontHandler
{
  public:
    explicit FontHandler(std::string path) noexcept;
    FontHandler(const FontHandler& other) noexcept = default;
    FontHandler(FontHandler&& other) noexcept      = default;
    ~FontHandler() noexcept                        = default;

    FontHandler& operator=(const FontHandler& rhs) noexcept = default;
    FontHandler& operator=(FontHandler&& rhs) noexcept      = default;

    Font getFont() const noexcept;
    int  getFontSize() const noexcept;
    void setFontSize(int size) noexcept;
    void unload() noexcept;

  protected:
  private:
    Font font_;
    int  font_size_ = 30;
};