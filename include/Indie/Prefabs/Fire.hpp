/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Fire
*/

#pragma once

#include "Entity.hpp"
#include "GameData.hpp"
#include "Timer.hpp"

class Fire : public Entity
{
  private:
    float                  explodeTime;
    std::unique_ptr<Timer> explodeTimer;

  public:
    Fire(Vector3 posi, std::unique_ptr<Model3D>* model);
    ~Fire() noexcept                          = default;
    Fire(const Fire& other) noexcept          = delete;
    Fire(Fire&& other) noexcept               = delete;
    Fire& operator=(const Fire& rhs) noexcept = delete;
    Fire& operator=(Fire&& rhs) noexcept = delete;

    void Display() final;
    void Update() final;
    void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept;
    bool ExplodeElements(std::unique_ptr<Entity>& other) noexcept;
};
