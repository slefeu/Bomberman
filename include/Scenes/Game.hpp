/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include <memory>
#include <vector>

#include "Entities.hpp"
#include "Scene.hpp"

class Game : public Scene
{
  private:
    std::vector<std::unique_ptr<Entities>> _entities;
    std::vector<std::unique_ptr<Entities>> _players;

  public:
    Game() noexcept;
    ~Game() noexcept = default;
    void resetCamera(Cameraman& camera) noexcept;
    void display3D(void) noexcept;
    void display2D(void) noexcept;
    void action(Cameraman& camera) noexcept;
};

#endif /* !GAME_HPP_ */
