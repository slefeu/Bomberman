/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Round
*/

#include "Round.hpp"

#include <math.h>

float Round::myRound(float x, int n) noexcept
{
    return (float)(int)(x * pow(10, n)) / pow(10, n);
}

Vector3 Round::roundVector(Vector3 x, int n) noexcept
{
    return { myRound(x.x, n), myRound(x.y, n), myRound(x.z, n) };
}