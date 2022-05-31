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

class Bomb : public Entities
{
  public:
    Bomb(Vector3                                pos,
        Player*                                 p,
        std::unique_ptr<Model3D>*               newModel,
        int                                     bombSize,
        GameData*                               data,
        std::vector<std::unique_ptr<Entities>>* entities);
    ~Bomb() noexcept                          = default;
    Bomb(const Bomb& other) noexcept          = delete;
    Bomb(Bomb&& other) noexcept               = delete;
    Bomb& operator=(const Bomb& rhs) noexcept = delete;
    Bomb& operator=(Bomb&& rhs) noexcept      = delete;

    void Display() final;
    void Update() final;
    void setPlayerArray(std::vector<std::unique_ptr<Player>>* players) noexcept;
    void explode() noexcept;
    void OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept final;

  private:
    // methods
    void createFire(Vector3 mul) noexcept;

    // attributes
    float                                   lifeTime;
    std::unique_ptr<Timer>                  lifeTimer;
    Player*                                 player;
    int                                     size;
    bool                                    hasHitbox;
    GameData*                               data;
    std::vector<std::unique_ptr<Entities>>* entities;
    std::vector<std::unique_ptr<Fire>>      fires;
    std::vector<std::unique_ptr<Player>>*   players;
    bool                                    is_exploding_;
    int                                     animeDir;
};
