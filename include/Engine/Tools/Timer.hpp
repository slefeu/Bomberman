/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Timer
*/

#pragma once

#include "raylib.h"

#define NEW_TIMER(time) std::make_unique<Timer>(time)

class Timer
{
  private:
    float lifeTime;

  public:
    Timer(float lifeTime) noexcept;
    ~Timer() noexcept = default;
    void  updateTimer(void) noexcept;
    bool  timerDone(void) noexcept;
    float getTime(void) noexcept;
    void  setLifeTime(float const& newLifeTime) noexcept;
};
