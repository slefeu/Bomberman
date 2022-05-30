/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Entities.hpp"
#include "Player.hpp"

#define NEW_ITEM(pos, data) std::make_unique<Item>((Vector3)pos, data)

enum class ItemType { I_SPEEDUP, I_BOMBUP, I_FIREUP };

class Item : public Entities
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
    void OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept;

  private:
    void setPlayerStat(std::unique_ptr<Player>& p) noexcept;

  private:
    ItemType itemType;
};

#pragma once
