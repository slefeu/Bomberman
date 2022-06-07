/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Mouse
*/

#include "Mouse.hpp"

#include "raylib.h"

void MouseHandler::update() noexcept
{
    Vector2 mouse = GetMousePosition();
    mouse_.x      = mouse.x;
    mouse_.y      = mouse.y;
}

bool MouseHandler::isColliding(const RectangleManager& bounds) noexcept
{
    Rectangle rectangle = { bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight() };

    Vector2 mouse = { mouse_.x, mouse_.y };

    if (CheckCollisionPointRec(mouse, rectangle)) {
        return (true);
    } else
        return (false);
}

bool MouseHandler::isClicking() const noexcept
{
    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) return (true);
    return (false);
}

bool MouseHandler::isClicked() const noexcept
{
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) return (true);
    return (false);
}
