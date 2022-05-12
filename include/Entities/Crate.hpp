/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#ifndef CRATE_HPP_
#define CRATE_HPP_

#include "Entities.hpp"

class Crate : public Entities
{
  public:
    Crate(Vector3 pos) noexcept;
    ~Crate() noexcept;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept;
    bool    update() noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
};

#endif /* !CRATE_HPP_ */
