/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#pragma once

#include <memory>
#include <vector>

#include "GameData.hpp"
#include "GameObject3D.hpp"

class Player : public GameObject3D
{
  private:
    KeyboardKey                                 moveUp;
    KeyboardKey                                 moveDown;
    KeyboardKey                                 moveLeft;
    KeyboardKey                                 moveRight;
    KeyboardKey                                 dropBomb;
    int                                         id;
    GameData*                                   data;
    std::vector<std::unique_ptr<GameObject3D>>* bombs;

  public:
    int   nbBomb;
    float speed;
    int   bombSize;

  public:
    Player(int newId, std::vector<std::unique_ptr<GameObject3D>>* bombsArray, GameData* data) noexcept;
    ~Player() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    void setStats(int bomb, int sp, int size) noexcept;
    void setBombArray(std::vector<std::unique_ptr<GameObject3D>>* bombsArray) noexcept;

  private:
    void setKeyboard(void) noexcept;
    void setPosition(void) noexcept;
    void placeBomb(void) noexcept;
    bool isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept;
};
