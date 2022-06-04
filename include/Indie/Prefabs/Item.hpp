/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Entity.hpp"
#include "Player.hpp"

enum class ItemType { I_SPEEDUP, I_BOMBUP, I_FIREUP, I_WALL };

class Item : public Entity
{
  public:
    Item(Vector3 pos, GameData* data);
    ~Item() noexcept                 = default;
    Item(const Item& other) noexcept = delete;
    Item(Item&& other) noexcept      = delete;
    Item& operator=(const Item& rhs) noexcept = delete;
    Item& operator=(Item&& rhs) noexcept = delete;

    void Display() final;
    void Update() final;
    void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept;

  private:
    void setPlayerStat(std::unique_ptr<Player>& p) noexcept;

  private:
    ItemType itemType;
};

#pragma once
