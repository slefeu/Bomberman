/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "GameObject3D.hpp"
#include "Player.hpp"

enum class ItemType { I_SPEEDUP, I_BOMBUP, I_FIREUP };

class Item : public GameObject3D
{
  public:
    Item(Vector3 pos, GameData* data) noexcept;
    ~Item() noexcept = default;
    void    display() noexcept;
    void    action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    Vector3 getPosition() noexcept;
    Vector3 getSize() noexcept;
    bool    isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    bool    isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept;
    bool    update() noexcept;
    bool    update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept;
    void    setLifeTime(float const& newLifeTime) noexcept;

  private:
    void moveX(float x) noexcept;
    void moveY(float y) noexcept;
    void moveZ(float z) noexcept;
    void setPlayerStat(std::unique_ptr<Player>& p) noexcept;

  private:
    ItemType itemType;
};

#endif /* !ITEM_HPP_ */
