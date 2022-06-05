/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Mouse
*/

#include "Mouse.hpp"

void MouseHandler::update() noexcept
{
    mouse_ = GetMousePosition();
}

bool MouseHandler::isColliding(const RectangleManager& bounds) noexcept
{
    Rectangle rectangle = { bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight() };

    if (CheckCollisionPointRec(mouse_, rectangle)) {
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
