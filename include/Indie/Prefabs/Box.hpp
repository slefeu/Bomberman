/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#pragma once

#include "Entities.hpp"

class Box : public Entities
{
  public:
    Box(Vector3 pos, Vector3 size);
    ~Box() noexcept                = default;
    Box(const Box& other) noexcept = delete;
    Box(Box&& other) noexcept      = delete;
    Box& operator=(const Box& rhs) noexcept = delete;
    Box& operator=(Box&& rhs) noexcept = delete;

    void Display() override;
    void Update() override;
};
