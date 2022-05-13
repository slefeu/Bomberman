/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Explosion
*/

#ifndef EXPLOSION_HPP_
#define EXPLOSION_HPP_

#include "Entities.hpp"
#include "Timer.hpp"

class Explosion : public Entities
{
  public:
    Explosion(Vector3 pos, float size) noexcept;
    ~Explosion() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept;
    bool    update(void) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    void CollideAction(std::unique_ptr<Entities>& other) noexcept;

  private:
    float                        lifeTime;
    std::unique_ptr<Timer>       timer;
    Vector3                      pos[4];
    Vector3                      siz[4];
    std::unique_ptr<BoxCollider> hitBoxHor;
    std::unique_ptr<BoxCollider> hitBoxVer;
};

#endif /* !EXPLOSION_HPP_ */
