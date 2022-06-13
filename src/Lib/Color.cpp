/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Color
*/

#include "Color.hpp"

ColorManager::ColorManager(const std::array<unsigned char, 3>& color) noexcept
{
    color_ = color;
}

void ColorManager::setColor(const std::array<unsigned char, 3>& color) noexcept
{
    color_ = color;
}

std::array<unsigned char, 3> ColorManager::getColor() const noexcept
{
    return (color_);
}