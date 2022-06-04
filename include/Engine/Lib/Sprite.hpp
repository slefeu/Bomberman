/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Sprite.cpp
*/

#pragma once

#include <string>

#include "Color.hpp"
#include "raylib.h"

enum class SpriteType { S_WHITE, S_RED, S_BLUE, S_BLACK, S_NONE };

class Sprite
{
  public:
    Sprite(const std::string& path) noexcept;
    Sprite(const std::string& path, float x, float y) noexcept;
    Sprite(const std::string& path, float x, float y, float scale) noexcept;
    Sprite(const Sprite& other) noexcept = default;
    Sprite(Sprite&& other) noexcept      = default;
    ~Sprite() noexcept                   = default;

    Sprite& operator=(const Sprite& rhs) noexcept = default;
    Sprite& operator=(Sprite&& rhs) noexcept = default;

    void  draw() const noexcept;
    void  draw(const std::array<unsigned char, 3>& color) const noexcept;
    void  setPos(float x, float y) noexcept;
    void  setScale(float scale) noexcept;
    int   getPosX() const noexcept;
    int   getPosY() const noexcept;
    float getWidth() const noexcept;
    float getHeight() const noexcept;
    void  unload() noexcept;

  protected:
  private:
    Image     image_;
    Texture2D texture_;
    float     pos_x_;
    float     pos_y_;
    float     scale_;
};