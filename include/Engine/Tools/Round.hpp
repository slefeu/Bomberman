/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Round
*/

#pragma once

#include "raylib.h"

class Round
{
  public:
    Round() noexcept                   = default;
    ~Round() noexcept                  = default;
    Round(const Round& other) noexcept = delete;
    Round(Round&& other) noexcept      = delete;
    Round& operator=(const Round& rhs) noexcept = delete;
    Round& operator=(Round&& rhs) noexcept = delete;

    float   myRound(const float& x, const int& n = 0) noexcept;
    Vector3 roundVector(const Vector3& x, const int& n = 0) noexcept;
};
