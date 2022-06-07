/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Controller
*/

#include "Controller.hpp"

#include "raylib.h"

bool Controller::isKeyDown(Key key) const noexcept
{
    return IsKeyDown(static_cast<KeyboardKey>(key));
}

bool Controller::isKeyPressed(Key key) const noexcept
{
    return IsKeyPressed(static_cast<KeyboardKey>(key));
}

bool Controller::isGamepadConnected(int id) const noexcept
{
    return IsGamepadAvailable(id);
}

bool Controller::isGamepadButtonPressed(int id, G_Button button) const noexcept
{
    return IsGamepadButtonPressed(id, static_cast<GamepadButton>(button));
}

float Controller::getGamepadAxis(int id, Axis axis) const noexcept
{
    return GetGamepadAxisMovement(id, static_cast<GamepadAxis>(axis));
}