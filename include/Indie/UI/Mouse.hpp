/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Mouse
*/

#pragma once
#include "raylib.h"

class MouseHandler
{
  public:
    MouseHandler() noexcept                          = default;
    MouseHandler(const MouseHandler& other) noexcept = default;
    MouseHandler(MouseHandler&& other) noexcept      = default;
    ~MouseHandler() noexcept                         = default;

    MouseHandler& operator=(const MouseHandler& rhs) noexcept = default;
    MouseHandler& operator=(MouseHandler&& rhs) noexcept = default;

    void    update() noexcept;
    Vector2 getPosition() const noexcept;

  protected:
  private:
    Vector2 mouse_ = { 0.0f, 0.0f };
};