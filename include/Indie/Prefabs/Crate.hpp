/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#pragma once
#include "Box.hpp"
#include "GameData.hpp"

#define NEW_CRATE(pos, data, entities) std::make_unique<Crate>((Vector3)pos, MODELS(M_CRATE), data, entities)

class Crate : public Box
{
  public:
    Crate(Vector3 pos, std::unique_ptr<Model3D>* model, GameData* data, std::vector<std::unique_ptr<GameObject3D>>* entities) noexcept;
    ~Crate() noexcept                           = default;
    Crate(const Crate& other) noexcept          = delete;
    Crate(Crate&& other) noexcept               = delete;
    Crate& operator=(const Crate& rhs) noexcept = delete;
    Crate& operator=(Crate&& rhs) noexcept      = delete;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    void dropItem() noexcept;

  public:
    GameData*                                   data;
    std::vector<std::unique_ptr<GameObject3D>>* entities;
};
