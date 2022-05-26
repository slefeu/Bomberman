/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Fire
*/

#pragma once

#include "GameData.hpp"
#include "GameObject3D.hpp"
#include "Timer.hpp"

class Fire : public GameObject3D
{
  public:
    Fire(Vector3 posi, float newSize) noexcept;
    ~Fire() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept;
    bool    update(void) noexcept;
    bool    update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    void    setLifeTime(float const& newLifeTime) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    void CollideAction(std::unique_ptr<GameObject3D>& other) noexcept;

  private:
    float                  lifeTime;
    std::unique_ptr<Timer> timer;
};
