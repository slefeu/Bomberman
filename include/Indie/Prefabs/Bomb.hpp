/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#pragma once

#include <math.h>

#include "Fire.hpp"
#include "Player.hpp"
#include "Timer.hpp"

class Bomb : public GameObject3D
{
  private:
    float                                       lifeTime;
    std::unique_ptr<Timer>                      lifeTimer;
    Player*                                     player;
    int                                         size;
    bool                                        hasHitbox;
    GameData*                                   data;
    std::vector<std::unique_ptr<GameObject3D>>* entities;
    std::vector<std::unique_ptr<Fire>>          fires;
    std::vector<std::unique_ptr<Player>>*       players;

  public:
    bool isExploding = false;

  public:
    Bomb(Vector3                                    pos,
        Player*                                     p,
        std::unique_ptr<Model3D>*                   newModel,
        int                                         bombSize,
        GameData*                                   data,
        std::vector<std::unique_ptr<GameObject3D>>* entities) noexcept;
    ~Bomb() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    void setPlayerArray(std::vector<std::unique_ptr<Player>>* players) noexcept;
    void explode() noexcept;

  private:
    void createFire(Vector3 mul) noexcept;
};
