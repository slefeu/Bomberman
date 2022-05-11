/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Clock
*/

#include "Clock.hpp"

Clock::Clock(float newLifeTime) noexcept
{
    lifeTime = newLifeTime;
}

void Clock::updateClock(void) noexcept
{
    currentTime += GetFrameTime();
}

bool Clock::clockDone(void) noexcept
{
    return (currentTime % lifeTime == 0);
}
