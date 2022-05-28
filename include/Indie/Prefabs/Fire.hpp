/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Fire
*/

#pragma once

#include "GameData.hpp"
#include "Entities.hpp"
#include "Timer.hpp"

#define NEW_FIRE(pos, size) std::make_unique<Fire>(pos, size)

class Fire : public Entities
{
  private:
    float                  explodeTime;
    std::unique_ptr<Timer> explodeTimer;

  public:
    Fire(Vector3 posi, float newSize);
    ~Fire() noexcept                          = default;
    Fire(const Fire& other) noexcept          = delete;
    Fire(Fire&& other) noexcept               = delete;
    Fire& operator=(const Fire& rhs) noexcept = delete;
    Fire& operator=(Fire&& rhs) noexcept      = delete;

    void Display() final;
    void Update() final;
    void OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept;
    bool ExplodeElements(std::unique_ptr<Entities>& other) noexcept;
};
