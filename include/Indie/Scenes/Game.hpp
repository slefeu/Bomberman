/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#pragma once

#include <math.h>

#include <memory>
#include <vector>

#include "GameObject3D.hpp"
#include "Model3D.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Game : public Scene
{
  private:
    std::vector<std::unique_ptr<GameObject3D>>  _entities;
    std::vector<std::unique_ptr<GameObject3D>>* _players;
    std::vector<std::unique_ptr<Model3D>>*      _models;
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
    void DestroyPool() noexcept;
    void CollisionPool() noexcept;

  private:
    void createMap(void) noexcept;
    void hurryUp(void) noexcept;
};
