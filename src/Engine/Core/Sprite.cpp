#include "Sprite.hpp"

Sprite::Sprite(std::string path) noexcept
    : image(LoadImage(path.c_str()))
    , texture(LoadTextureFromImage(image))
    , posX(0)
    , posY(0)
    , scale(1.0f)
{
}

Sprite::Sprite(std::string path, float x, float y) noexcept
    : image(LoadImage(path.c_str()))
    , texture(LoadTextureFromImage(image))
    , posX(x)
    , posY(y)
    , scale(1.0f)
{
}

Sprite::Sprite(std::string path, float x, float y, float scale) noexcept
    : image(LoadImage(path.c_str()))
    , texture(LoadTextureFromImage(image))
    , posX(x)
    , posY(y)
    , scale(scale)
{
}

Sprite::~Sprite() noexcept
{
    UnloadImage(image);
    UnloadTexture(texture);
}

void Sprite::setPos(float x, float y) noexcept
{
    posX = x;
    posY = y;
}

int Sprite::getPosX() const noexcept
{
    return posX;
}

int Sprite::getPosY() const noexcept
{
    return posY;
}

void Sprite::draw() noexcept
{
    DrawTextureEx(texture, { posX, posY }, 0.0f, scale, WHITE);
}

void Sprite::setScale(float scale) noexcept
{
    this->scale = scale;
}