/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** DeltaTime
*/

#include "DeltaTime.hpp"

#include "raylib.h"

float DeltaTime::getDeltaTime() noexcept
{
    return GetFrameTime();
}