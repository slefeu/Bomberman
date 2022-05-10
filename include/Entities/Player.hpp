/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include "Entities.hpp"

class Player : public Entities
{
  public:
    Player(int id) noexcept;
    Player(int newId, Color newColor) noexcept;
    Player(Vector3 pos, Vector3 size, Color color, int id) noexcept;
    ~Player() noexcept = default;
    void display() noexcept;
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    void action(void) noexcept;

  private:
    void setKeyboard(void) noexcept;
};

#endif /* !PLAYER_HPP_ */
