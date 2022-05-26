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

class Fire : public GameObject3D
{
  public:
    Fire(Vector3 posi, float newSize) noexcept;
    ~Fire() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    // void setLifeTime(float const& newLifeTime) noexcept;

    // private:
    // void CollideAction(std::unique_ptr<GameObject3D>& other) noexcept;

  private:
    float                  lifeTime;
    std::unique_ptr<Timer> timer;
};
