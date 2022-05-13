/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <memory>
#include <vector>

#include "GameObject3D.hpp"

class Player : public GameObject3D
{
  private:
    KeyboardKey                moveUp;
    KeyboardKey                moveDown;
    KeyboardKey                moveLeft;
    KeyboardKey                moveRight;
    KeyboardKey                dropBomb;
    int                        id;
    float                      speed;
    std::unique_ptr<Render3D>* bombModel;

  public:
    std::vector<std::unique_ptr<GameObject3D>>* bombs;
    int                                         nbBomb;

  public:
    Player(int                                      newId,
        Color                                       newColor,
        std::vector<std::unique_ptr<GameObject3D>>* bombs,
        std::unique_ptr<Render3D>*                  _bombModel) noexcept;
    ~Player() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept;
    bool    update() noexcept;

  private:
    void setKeyboard(void) noexcept;
    void setPosition(void) noexcept;
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    void placeBomb(void) noexcept;
};

#endif /* !PLAYER_HPP_ */
