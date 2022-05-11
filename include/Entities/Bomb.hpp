/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include "Entities.hpp"
#include "Timer.hpp"

class Bomb : public Entities
{
  public:
    Bomb(Vector3 pos) noexcept;
    ~Bomb() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept;
    bool    update(void) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;

  private:
    float                  lifeTime;
    std::unique_ptr<Timer> timer;
};

#endif /* !BOMB_HPP_ */
