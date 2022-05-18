/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <math.h>

#include <memory>
#include <vector>

#include "GameObject3D.hpp"
#include "Render3D.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Game : public Scene
{
  private:
    std::vector<std::unique_ptr<GameObject3D>>  _entities;
    std::vector<std::unique_ptr<GameObject3D>>  _bombs;
    std::vector<std::unique_ptr<GameObject3D>>* _players;
    std::vector<std::unique_ptr<GameObject3D>>  _items;
    std::vector<std::unique_ptr<Render3D>>*     _models;
    std::unique_ptr<Timer>                      _chrono;

  private:
    float     lastTimeBlockPlace;
    bool      isHurry;
    int       nbBlockPlaced;
    int       x         = -6;
    int       z         = 7;
    int       maxX      = 6;
    int       maxZ      = 6;
    int       minX      = -5;
    int       minZ      = -4;
    Direction direction = Direction::UP;

  public:
    Game(GameData* data) noexcept;
    ~Game() noexcept = default;
    void resetCamera(Cameraman& camera) noexcept;
    void display3D(void) noexcept;
    void display2D(void) noexcept;
    void action(Cameraman& camera) noexcept;

  private:
    void createMap(void) noexcept;
    void hurryUp(void) noexcept;
};

#endif /* !GAME_HPP_ */
