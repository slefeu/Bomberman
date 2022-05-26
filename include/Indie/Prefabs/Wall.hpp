/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#pragma once

#include "Crate.hpp"

class Wall : public Crate
{
  public:
    Wall(Vector3 pos, std::unique_ptr<Model3D>* model, GameData* data) noexcept;
    ~Wall() noexcept = default;
    void display() noexcept;
};
