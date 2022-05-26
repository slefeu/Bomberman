/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#pragma once
#include "Box.hpp"
#include "GameData.hpp"

class Crate : public Box
{
  public:
    Crate(Vector3 pos, std::unique_ptr<Model3D>* model, GameData* data) noexcept;
    ~Crate() noexcept = default;
    void display() noexcept;
    void dropItem() noexcept;

  public:
    GameData* data;
};
