/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Timer
*/

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "raylib.h"

class Timer
{
  private:
    float lifeTime;

  public:
    Timer(float lifeTime) noexcept;
    ~Timer() noexcept = default;
    void updateTimer(void) noexcept;
    bool timerDone(void) noexcept;
};

#endif /* !TIMER_HPP_ */
