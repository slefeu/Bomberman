/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Sprite.cpp
*/

#pragma once

#include <string>

#include "raylib.h"

#define NEW_SPRITE(path) std::make_unique<Sprite>(path)
#define NEW_SPRITE_POS(path, x, y) std::make_unique<Sprite>(path, x, y)

class Sprite
{
  private:
    Image     image;
    Texture2D texture;
    int       posX;
    int       posY;

  public:
    Sprite(std::string path) noexcept;
    Sprite(std::string path, int x, int y) noexcept;
    ~Sprite() noexcept;
    Sprite(const Sprite& other) noexcept = delete;
    Sprite(Sprite&& other) noexcept      = delete;

    Sprite& operator=(const Sprite& rhs) noexcept = delete;
    Sprite& operator=(Sprite&& rhs) noexcept      = delete;

    void draw() noexcept;
    void setPos(int x, int y) noexcept;
    int  getPosX() const noexcept;
    int  getPosY() const noexcept;
};