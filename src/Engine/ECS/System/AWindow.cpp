/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** AWindow
*/

#include "AWindow.hpp"

AWindow::AWindow(int width, int height, int fps) noexcept
    : width_(width)
    , height_(height)
    , fps_(fps)
{
}

int AWindow::getWidth() const noexcept
{
    return (width_);
}

int AWindow::getHeight() const noexcept
{
    return (height_);
}
float AWindow::getFps() const noexcept
{
    return (fps_);
}
