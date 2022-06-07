/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#pragma once

#include "Entity.hpp"
#include "Player.hpp"
#include "Sound.hpp"

enum class ItemType { I_SPEEDUP, I_BOMBUP, I_FIREUP, I_WALL };

static const inline char* GET_ITEM = "assets/audios/GetItem.wav";
static const inline char* NEW_ITEM = "assets/audios/NewItem.wav";

class Item : public Entity
{
  public:
    Item(Vector3D pos, GameData* data);
    ~Item() noexcept;
    Item(GameData* data, ItemType type);
    Item(const Item& other) noexcept          = delete;
    Item(Item&& other) noexcept               = delete;
    Item& operator=(const Item& rhs) noexcept = delete;
    Item& operator=(Item&& rhs) noexcept      = delete;

    void Display() final;
    void Update() final;
    void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept;

  private:
    void     setPlayerStat(std::unique_ptr<Player>& p) noexcept;
    Vector3D findFreePosition(void) const noexcept;
    bool     entitiesHere(Vector3D& pos) const noexcept;
    void     setModelByType(void) noexcept;

  private:
    GameData*    data;
    ItemType     itemType;
    SoundManager getItemSound;
    SoundManager newItemSound;
};
