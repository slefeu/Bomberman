/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Round
*/

#ifndef ROUND_HPP_
#define ROUND_HPP_

#include "raylib.h"

class Round
{
  public:
    Round() noexcept  = default;
    ~Round() noexcept = default;
    float   myRound(float x, int n = 0) noexcept;
    Vector3 roundVector(Vector3 x, int n = 0) noexcept;
};

#endif /* !ROUND_HPP_ */
