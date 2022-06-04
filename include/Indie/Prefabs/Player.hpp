/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#pragma once

#include <memory>
#include <vector>

#include "Entity.hpp"
#include "GameData.hpp"
#include "Timer.hpp"

#define NEW_PLAYER(id, data) std::make_unique<Player>(id, data)

enum class PlayerType { NORMAL, ATTACK, TACTICAL, RUNNER };

class Player : public Entity
{
  public:
    Player(const int newId, GameData* data);
    ~Player() noexcept                            = default;
    Player(const Player& other) noexcept          = delete;
    Player(Player&& other) noexcept               = delete;
    Player& operator=(const Player& rhs) noexcept = delete;
    Player& operator=(Player&& rhs) noexcept      = delete;

    void  Display() final;
    void  Update() final;
    void  OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept;
    void  setStats(int bomb, int sp, int size) noexcept;
    void  setBombArray(std::vector<std::unique_ptr<Entity>>* bombsArray) noexcept;
    void  setPlayerType(PlayerType type) noexcept;
    void  setWallPass(const bool& pass) noexcept;
    int   getNbBombMax(void) const noexcept;
    float getSpeedMax(void) const noexcept;
    int   getBombSizeMax(void) const noexcept;
    float getSpeed() const noexcept;
    int   getNbBomb() const noexcept;
    int   getBombSize() const noexcept;
    void  setSpeed(const int& speed) noexcept;
    void  setNbBomb(const int& nbBomb) noexcept;
    void  setBombSize(const int& bombSize) noexcept;

  private:
    void      setKeyboard(void) noexcept;
    void      setPosition(void);
    void      placeBomb(void);
    bool      isCollidingNextTurn(std::vector<std::unique_ptr<Entity>>& others, int xdir, int zdir);
    Key       moveUp;
    Key       moveDown;
    Key       moveLeft;
    Key       moveRight;
    Key       dropBomb;
    int       id;
    GameData* data;
    std::vector<std::unique_ptr<Entity>>* bombs;
    bool                                  wallpass;
    std::unique_ptr<Timer>                wallpassTimer;
    bool                                  wallpassEnd;
    int                                   nbBomb;
    float                                 speed;
    int                                   bombSize;
    int                                   nbBombMax;
    float                                 speedMax;
    int                                   bombSizeMax;
    PlayerType                            type;
    int                                   colorIndex = 0;
    std::vector<Color>                    colors     = { LIGHTGRAY,
                               GRAY,
                               YELLOW,
                               GOLD,
                               ORANGE,
                               PINK,
                               RED,
                               MAROON,
                               GREEN,
                               LIME,
                               DARKGREEN,
                               SKYBLUE,
                               BLUE,
                               DARKBLUE,
                               PURPLE,
                               VIOLET,
                               DARKPURPLE,
                               BEIGE,
                               BROWN,
                               DARKBROWN };
};
