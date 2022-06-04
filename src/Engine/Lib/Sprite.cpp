/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Sprite
*/

#include "Sprite.hpp"

Sprite::Sprite(const std::string& path) noexcept
    : image_(LoadImage(path.c_str()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(0)
    , pos_y_(0)
    , scale_(1.0f)
{
}

Sprite::Sprite(const std::string& path, float x, float y) noexcept
    : image_(LoadImage(path.c_str()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(x)
    , pos_y_(y)
    , scale_(1.0f)
{
}

Sprite::Sprite(const std::string& path, float x, float y, float scale) noexcept
    : image_(LoadImage(path.c_str()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(x)
    , pos_y_(y)
    , scale_(scale)
{
}

void Sprite::unload() noexcept
{
    UnloadImage(image_);
    UnloadTexture(texture_);
}

void Sprite::setPos(float x, float y) noexcept
{
    pos_x_ = x;
    pos_y_ = y;
}

int Sprite::getPosX() const noexcept
{
    return pos_x_;
}

int Sprite::getPosY() const noexcept
{
    return pos_y_;
}

void Sprite::draw() const noexcept
{
    DrawTextureEx(texture_, { pos_x_, pos_y_ }, 0.0f, scale_, WHITE);
}

void Sprite::draw(const std::array<unsigned char, 3>& color) const noexcept
{
    DrawTextureEx(
        texture_, { pos_x_, pos_y_ }, 0.0f, scale_, (Color){ color[0], color[1], color[2], 255 });
}

void Sprite::setScale(float scale) noexcept
{
    scale_ = scale;
}

float Sprite::getWidth() const noexcept
{
    return (texture_.width);
}

float Sprite::getHeight() const noexcept
{
    return (texture_.height);
}