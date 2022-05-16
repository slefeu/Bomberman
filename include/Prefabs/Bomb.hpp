/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#ifndef BOMB_HPP_
#define BOMB_HPP_

#include <math.h>

#include "Explosion.hpp"
#include "Player.hpp"
#include "Timer.hpp"

class Bomb : public GameObject3D
{
  public:
    Bomb(Vector3 pos, Player* p, std::unique_ptr<Render3D>* model, int bombSize) noexcept;
    ~Bomb() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept;
    bool    update(void) noexcept;
    bool    update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;

  private:
    float                      lifeTime;
    std::unique_ptr<Timer>     lifeTimer;
    std::unique_ptr<Explosion> explosion;
    Player*                    player;
    int                        size;
};

#endif /* !BOMB_HPP_ */
