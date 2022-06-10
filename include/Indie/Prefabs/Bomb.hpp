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
#include "Sound.hpp"
#include "Timer.hpp"

static const inline char* DROP_BOMB = "assets/audios/DropBomb.wav";
static const inline char* EXPLODE   = "assets/audios/Explode.wav";

class Bomb : public Entity
{
  public:
    Bomb(Vector3D                             pos,
        Player*                               p,
        std::unique_ptr<Model3D>*             newModel,
        int                                   bombSize,
        GameData*                             data,
        std::vector<std::unique_ptr<Entity>>* Entity);
    ~Bomb() noexcept;
    Bomb(const Bomb& other) noexcept          = delete;
    Bomb(Bomb&& other) noexcept               = delete;
    Bomb& operator=(const Bomb& rhs) noexcept = delete;
    Bomb& operator=(Bomb&& rhs) noexcept      = delete;

    void Display() final;
    void Update() final;
    void setPlayerArray(std::vector<std::unique_ptr<Player>>* players) noexcept;
    void explode() noexcept;
    void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept final;
    int  getLifeTime() const noexcept;

  private:
    // methods
    void createFire(Vector3D mul) noexcept;

    // attributes
    float                                 lifeTime;
    std::unique_ptr<Timer>                lifeTimer;
    Player*                               player;
    int                                   size;
    bool                                  hasHitbox;
    GameData*                             data;
    std::vector<std::unique_ptr<Entity>>* entities;
    std::vector<std::unique_ptr<Fire>>    fires;
    std::vector<std::unique_ptr<Player>>* players;
    bool                                  is_exploding_;
    int                                   animeDir;
    SoundManager                          dropSound_;
    SoundManager                          explodeSound;
};
