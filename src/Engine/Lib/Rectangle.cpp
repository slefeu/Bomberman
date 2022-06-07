/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Rectangle
*/

#include "Rectangle.hpp"

RectangleManager::RectangleManager(float x, float y, float width, float height) noexcept
    : x_(x)
    , y_(y)
    , width_(width)
    , height_(height)
{
}

float RectangleManager::getX() const noexcept
{
    return (x_);
}

float RectangleManager::getY() const noexcept
{
    return (y_);
}

float RectangleManager::getWidth() const noexcept
{
    return (width_);
}

float RectangleManager::getHeight() const noexcept
{
    return (height_);
}

void RectangleManager::setPos(float x, float y) noexcept
{
    x_ = x;
    y_ = y;
}

void RectangleManager::setWidth(float width) noexcept
{
    width_ = width;
}

void RectangleManager::setHeight(float height) noexcept
{
    height_ = height;
}