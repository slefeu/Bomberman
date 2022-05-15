/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Fire
*/

#ifndef FIRE_HPP_
#define FIRE_HPP_

#include "GameObject3D.hpp"
#include "Timer.hpp"

class Fire : public GameObject3D
{
  public:
    Fire(Vector3 pos, float size) noexcept;
    ~Fire() noexcept = default;
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
    void CollideAction(std::unique_ptr<GameObject3D>& other) noexcept;

  private:
    float                  lifeTime;
    std::unique_ptr<Timer> timer;
};

#endif /* !FIRE_HPP_ */
