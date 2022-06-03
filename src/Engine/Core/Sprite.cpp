#include "Sprite.hpp"

Sprite::Sprite(std::string path) noexcept
    : image(LoadImage(path.c_str()))
    , texture(LoadTextureFromImage(image))
    , posX(0)
    , posY(0)
{
}

Sprite::Sprite(std::string path, int x, int y) noexcept
    : image(LoadImage(path.c_str()))
    , texture(LoadTextureFromImage(image))
    , posX(x)
    , posY(y)
{
}

Sprite::~Sprite() noexcept
{
    UnloadImage(image);
    UnloadTexture(texture);
}

void Sprite::setPos(int x, int y) noexcept
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
    DrawTexture(texture, posX, posY, WHITE);
}