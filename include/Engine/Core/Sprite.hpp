/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Sprite.cpp
*/

#pragma once

#include <string>

#include "raylib.h"

enum class SpriteType { S_WHITE, S_RED, S_BLUE, S_BLACK, S_NONE };

class Sprite
{
  private:
    Image     image;
    Texture2D texture;
    float     posX;
    float     posY;
    float     scale;

  public:
    Sprite(std::string path) noexcept;
    Sprite(std::string path, float x, float y) noexcept;
    Sprite(std::string path, float x, float y, float scale) noexcept;
    ~Sprite() noexcept;
    Sprite(const Sprite& other) noexcept = delete;
    Sprite(Sprite&& other) noexcept      = delete;

    Sprite& operator=(const Sprite& rhs) noexcept = delete;
    Sprite& operator=(Sprite&& rhs) noexcept      = delete;

    void draw() noexcept;
    void setPos(float x, float y) noexcept;
    int  getPosX() const noexcept;
    int  getPosY() const noexcept;
    void setScale(float scale) noexcept;
};