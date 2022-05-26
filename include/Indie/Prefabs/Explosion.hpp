/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Explosion
*/

#pragma once

#include "Fire.hpp"
#include "GameData.hpp"
#include "GameObject3D.hpp"
#include "Timer.hpp"

class Explosion : public GameObject3D
{
  public:
    Explosion(Vector3 pos, int size, std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    ~Explosion() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    // void setLifeTime(float const& newLifeTime) noexcept;

  private:
    void CollideAction(std::unique_ptr<GameObject3D>& other) noexcept;
    // void extandExplosion(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;

  private:
    float                              lifeTime;
    std::unique_ptr<Timer>             timer;
    std::vector<std::unique_ptr<Fire>> fires;
    int                                explosionSize;
    GameData*                          data;
};
