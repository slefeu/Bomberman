/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Mouse
*/

#include "Mouse.hpp"

#include <iostream>

Vector2 MouseHandler::getPosition() const noexcept
{
    return (mouse_);
}

void MouseHandler::update() noexcept
{
    mouse_ = GetMousePosition();
}