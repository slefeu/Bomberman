/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Fire
*/

#pragma once

#include "GameData.hpp"
#include "GameObject3D.hpp"
#include "Timer.hpp"

#define NEW_FIRE(pos, size) std::make_unique<Fire>(pos, size)

class Fire : public GameObject3D
{
  private:
    float                  explodeTime;
    std::unique_ptr<Timer> explodeTimer;

  public:
    Fire(Vector3 posi, float newSize) noexcept;
    ~Fire() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    bool ExplodeElements(std::unique_ptr<GameObject3D>& other) noexcept;
};
