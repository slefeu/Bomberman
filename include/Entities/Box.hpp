/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#ifndef BOX_HPP_
#define BOX_HPP_

#include "Entities.hpp"

class Box : public Entities
{
    // private:
    // Model     model;
    // Texture2D texture;

  public:
    Box(Vector3 pos, float scale) noexcept;
    ~Box() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<Entities>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
};

#endif /* !BOX_HPP_ */
