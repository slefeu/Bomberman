/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Timer
*/

#pragma once

#include "raylib.h"

class Timer
{
  private:
    float lifeTime;
    float defaultTime;

  public:
    Timer(float lifeTime) noexcept;
    ~Timer() noexcept                  = default;
    Timer(const Timer& other) noexcept = delete;
    Timer(Timer&& other) noexcept      = delete;
    Timer& operator=(const Timer& rhs) noexcept = delete;
    Timer& operator=(Timer&& rhs) noexcept = delete;

    void  updateTimer() noexcept;
    bool  timerDone() const noexcept;
    float getTime() const noexcept;
    void  setLifeTime(float const& newLifeTime) noexcept;
    void  resetTimer() noexcept;
};
