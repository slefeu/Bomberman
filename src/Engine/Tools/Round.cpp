/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Round
*/

#include "Round.hpp"

#include <math.h>

float Round::round(const float& x, const int& n) noexcept
{
    return (float)(int)(x * pow(10, n)) / pow(10, n);
}

Vector3D Round::roundVector(const Vector3D& x, const int& n) noexcept
{
    return { Round::round(x.x, n), Round::round(x.y, n), Round::round(x.z, n) };
}
