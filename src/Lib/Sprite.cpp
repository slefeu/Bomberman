/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Sprite
*/

#include "Sprite.hpp"

Sprite::Sprite(const std::string_view& path) noexcept
    : image_(LoadImage(path.data()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(0)
    , pos_y_(0)
    , scale_(1.0f)
{
}

Sprite::Sprite(const std::string_view& path, float x, float y) noexcept
    : image_(LoadImage(path.data()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(x)
    , pos_y_(y)
    , scale_(1.0f)
{
}

Sprite::Sprite(const std::string_view& path, float x, float y, float scale) noexcept
    : image_(LoadImage(path.data()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(x)
    , pos_y_(y)
    , scale_(scale)
{
}

Sprite::Sprite(const std::string_view& path, float x, float y, float scale, bool display) noexcept
    : image_(LoadImage(path.data()))
    , texture_(LoadTextureFromImage(image_))
    , pos_x_(x)
    , pos_y_(y)
    , scale_(scale)
    , displayed_(display)
{
}

Sprite::Sprite(Sprite&& other) noexcept
    : image_(std::move(other.image_))
    , texture_(std::move(other.texture_))
    , pos_x_(other.pos_x_)
    , pos_y_(other.pos_y_)
    , scale_(other.scale_)
    , displayed_(other.displayed_)
    , unloaded_(other.unloaded_)
{
    other.unloaded_ = true;
}

Sprite& Sprite::operator=(Sprite&& rhs) noexcept
{
    image_        = std::move(rhs.image_);
    texture_      = std::move(rhs.texture_);
    pos_x_        = rhs.pos_x_;
    pos_y_        = rhs.pos_y_;
    scale_        = rhs.scale_;
    displayed_    = rhs.displayed_;
    unloaded_     = rhs.unloaded_;
    rhs.unloaded_ = true;
    return *(this);
}

Sprite::~Sprite() noexcept
{
    this->unload();
}

void Sprite::unload() noexcept
{
    if (!unloaded_) {
        UnloadImage(image_);
        UnloadTexture(texture_);
        unloaded_ = true;
    }
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
    if (displayed_) { DrawTextureEx(texture_, { pos_x_, pos_y_ }, 0.0f, scale_, WHITE); }
}

void Sprite::draw(const std::array<unsigned char, 3>& color) const noexcept
{
    Color col = { color[0], color[1], color[2], 255 };

    if (displayed_) {
        DrawTextureEx(texture_,
            { pos_x_, pos_y_ },
            0.0f,
            scale_,
            col);
    }
}

void Sprite::draw(const std::array<unsigned char, 4>& color) const noexcept
{
    Color col = { color[0], color[1], color[2], color[3] };

    if (displayed_) {
        DrawTextureEx(texture_,
            { pos_x_, pos_y_ },
            0.0f,
            scale_,
            col);
    }
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

void Sprite::setDisplay(bool value) noexcept
{
    displayed_ = value;
}

void Sprite::invertDisplay() noexcept
{
    displayed_ = !displayed_;
}

bool Sprite::getDisplay() const noexcept
{
    return (displayed_);
}