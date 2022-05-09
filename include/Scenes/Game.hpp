/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

#include "Scene.hpp"

class Game : public Scene
{
  public:
    Game() noexcept;
    ~Game() noexcept = default;
    void placeCamera(Cameraman& camera) noexcept;
    void display(void) noexcept;
    void action() noexcept;
};

#endif /* !GAME_HPP_ */
