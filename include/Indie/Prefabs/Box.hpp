/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#pragma once

#include "GameObject3D.hpp"

class Box : public GameObject3D
{
  public:
    Box(Vector3 pos, Vector3 size) noexcept;
    ~Box() noexcept                         = default;
    Box(const Box& other) noexcept          = delete;
    Box(Box&& other) noexcept               = delete;
    Box& operator=(const Box& rhs) noexcept = delete;
    Box& operator=(Box&& rhs) noexcept      = delete;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
};
