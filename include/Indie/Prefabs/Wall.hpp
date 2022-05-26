/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#pragma once

#define NEW_WALL(pos) std::make_unique<Wall>(vectorTemp, MODELS(M_WALL))

#include "Crate.hpp"

class Wall : public Crate
{
  public:
    Wall(Vector3 pos, std::unique_ptr<Model3D>* model) noexcept;
    ~Wall() noexcept                          = default;
    Wall(const Wall& other) noexcept          = delete;
    Wall(Wall&& other) noexcept               = delete;
    Wall& operator=(const Wall& rhs) noexcept = delete;
    Wall& operator=(Wall&& rhs) noexcept      = delete;

    void Update() noexcept;
};
