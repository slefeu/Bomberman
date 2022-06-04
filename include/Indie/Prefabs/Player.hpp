/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#pragma once

#include <memory>
#include <vector>

#include "Color.hpp"
#include "Entity.hpp"
#include "GameData.hpp"
#include "Timer.hpp"

enum class PlayerType { NORMAL, ATTACK, TACTICAL, RUNNER };

class Player : public Entity
{
  public:
    Player(const int newId, GameData* data);
    ~Player() noexcept                   = default;
    Player(const Player& other) noexcept = delete;
    Player(Player&& other) noexcept      = delete;
    Player& operator=(const Player& rhs) noexcept = delete;
    Player& operator=(Player&& rhs) noexcept = delete;

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
    void  setSpeed(const float& speed) noexcept;
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
    std::vector<std::unique_ptr<Entity>>*     bombs;
    bool                                      wallpass;
    std::unique_ptr<Timer>                    wallpassTimer;
    bool                                      wallpassEnd;
    int                                       nbBomb;
    float                                     speed;
    int                                       bombSize;
    int                                       nbBombMax;
    float                                     speedMax;
    int                                       bombSizeMax;
    PlayerType                                type;
    int                                       colorIndex = 0;
    std::vector<std::array<unsigned char, 3>> colors     = { Colors::C_LIGHTGRAY,
        Colors::C_GRAY,
        Colors::C_YELLOW,
        Colors::C_GOLD,
        Colors::C_ORANGE,
        Colors::C_PINK,
        Colors::C_RED,
        Colors::C_MAROON,
        Colors::C_GREEN,
        Colors::C_LIME,
        Colors::C_DARKGREEN,
        Colors::C_SKYBLUE,
        Colors::C_BLUE,
        Colors::C_DARKBLUE,
        Colors::C_PURPLE,
        Colors::C_VIOLET,
        Colors::C_DARKPURPLE,
        Colors::C_BEIGE,
        Colors::C_BROWN,
        Colors::C_DARKBROWN };
};
