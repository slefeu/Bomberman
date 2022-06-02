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

#include "Entities.hpp"
#include "Model3D.hpp"
#include "Scene.hpp"
#include "Timer.hpp"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Game : public Scene
{
  public:
    Game(GameData* data) noexcept;
    ~Game() noexcept;
    Game(const Game& other) noexcept          = delete;
    Game(Game&& other) noexcept               = delete;
    Game& operator=(const Game& rhs) noexcept = delete;
    Game& operator=(Game&& rhs) noexcept      = delete;

    void resetCamera(Cameraman& camera) noexcept final;
    void display3D(void) noexcept final;
    void display2D(void) noexcept final;
    void action(Cameraman& camera) noexcept final;
    void DestroyPool() noexcept final;
    void CollisionPool() noexcept final;
    void playMusic() const noexcept final;
    Music getLoopMusic() const noexcept final;

  private:

    //methods
    void createMap(void) noexcept;
    void hurryUp(void) noexcept;

    //attributes
    std::vector<std::unique_ptr<Entities>>  _entities;
    std::vector<std::unique_ptr<Entities>>* _players;
    std::vector<std::unique_ptr<Model3D>>*  _models;
    std::unique_ptr<Timer>                  _chrono
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
    Music loop_music_;
};
