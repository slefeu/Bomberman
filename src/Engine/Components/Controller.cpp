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

ComponentType Controller::getComponentType() const noexcept
{
    return this->TYPE;
}