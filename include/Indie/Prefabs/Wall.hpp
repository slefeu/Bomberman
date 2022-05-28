/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#pragma once

#include "Shortcuts.hpp"
#include "Crate.hpp"

class Wall : public Crate
{
  public:
    Wall(Vector3 pos, std::unique_ptr<Model3D>* model);
    Wall(const Wall& other) noexcept = default;
    Wall(Wall&& other) noexcept      = default;
    ~Wall() noexcept                 = default;

    Wall& operator=(const Wall& rhs) noexcept = default;
    Wall& operator=(Wall&& rhs) noexcept = default;

    void Update() final;

  protected:
  private:
};