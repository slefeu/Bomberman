/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "GameObject3D.hpp"
#include "Player.hpp"

enum class ItemType { I_SPEEDUP, I_BOMBUP, I_FIREUP };

class Item : public GameObject3D
{
  public:
    Item(Vector3 pos, GameData* data) noexcept;
    ~Item() noexcept = default;

    void Display() noexcept;
    void Update() noexcept;
    void OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept;
    // void setLifeTime(float const& newLifeTime) noexcept;

  private:
    void setPlayerStat(std::unique_ptr<Player>& p) noexcept;

  private:
    ItemType itemType;
};

#pragma once
