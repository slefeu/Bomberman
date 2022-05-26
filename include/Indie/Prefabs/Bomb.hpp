/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#pragma once

#include <math.h>

#include "Explosion.hpp"
#include "Player.hpp"
#include "Timer.hpp"

class Bomb : public GameObject3D
{
  public:
    Bomb(Vector3 pos, Player* p, std::unique_ptr<Model3D>* model, int bombSize) noexcept;
    ~Bomb() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    // void setLifeTime(float const& newLifeTime) noexcept;

  private:
    float                      lifeTime;
    std::unique_ptr<Timer>     lifeTimer;
    std::unique_ptr<Explosion> explosion;
    Player*                    player;
    int                        size;
    bool                       hasHitbox;
};
