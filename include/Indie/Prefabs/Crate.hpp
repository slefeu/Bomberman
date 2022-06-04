/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#pragma once
#include "Entity.hpp"
#include "GameData.hpp"
#include "Shortcuts.hpp"

class Crate : public Entity
{
  public:
    Crate(Vector3                             pos,
        std::unique_ptr<Model3D>*             model,
        GameData*                             data,
        std::vector<std::unique_ptr<Entity>>* Entity);
    ~Crate() noexcept                           = default;
    Crate(const Crate& other) noexcept          = delete;
    Crate(Crate&& other) noexcept               = delete;
    Crate& operator=(const Crate& rhs) noexcept = delete;
    Crate& operator=(Crate&& rhs) noexcept      = delete;

    void Display() override;
    void Update() override;
    void dropItem();
    void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept final;

  public:
    GameData*                             data;
    std::vector<std::unique_ptr<Entity>>* entities;
};
