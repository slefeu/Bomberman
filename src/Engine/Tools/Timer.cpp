/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Timer
*/

#include "Timer.hpp"

#include "DeltaTime.hpp"

Timer::Timer(float time) noexcept
    : life_time_(time)
    , default_(time)
{
}

void Timer::updateTimer() noexcept
{
    if (life_time_ > 0) life_time_ -= DeltaTime::getDeltaTime();
}

bool Timer::isTimerDone() const noexcept
{
    return (life_time_ <= 0);
}

float Timer::getTime() const noexcept
{
    return (life_time_);
}

void Timer::setLifeTime(float time) noexcept
{
    life_time_ = time;
}

void Timer::resetTimer() noexcept
{
    life_time_ = default_;
}
