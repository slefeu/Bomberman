/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Timer
*/

#include "Timer.hpp"

Timer::Timer(float newLifeTime) noexcept
    : lifeTime(newLifeTime)
    , defaultTime(newLifeTime)
{
}

void Timer::updateTimer() noexcept
{
    if (lifeTime > 0) lifeTime -= GetFrameTime();
}

bool Timer::timerDone() const noexcept
{
    return lifeTime <= 0;
}

float Timer::getTime() const noexcept
{
    return lifeTime;
}

void Timer::setLifeTime(float const& newLifeTime) noexcept
{
    lifeTime = newLifeTime;
}

void Timer::resetTimer() noexcept
{
    lifeTime = defaultTime;
}
