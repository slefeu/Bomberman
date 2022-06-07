/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#pragma once

#include <memory>
#include <vector>

#include "Entities.hpp"
#include "GameData.hpp"
#include "Timer.hpp"

#define NEW_PLAYER(id, data) std::make_unique<Player>(id, data)

enum class ItemType;

class Player : public Entities
{
  public:
    Player(const int newId, GameData* data);
    ~Player() noexcept                            = default;
    Player(const Player& other) noexcept          = delete;
    Player(Player&& other) noexcept               = delete;
    Player& operator=(const Player& rhs) noexcept = delete;
    Player& operator=(Player&& rhs) noexcept      = delete;

    void Display() final;
    void Update() final;
    void OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept;
    void setBombArray(std::vector<std::unique_ptr<Entities>>* bombsArray) noexcept;
    void setWallPass(const bool& pass);
    void dispatchItem(void) noexcept;
    void addItem(ItemType item) noexcept;

  public:
    int   nbBomb;
    float speed;
    int   bombSize;

  private:
    void        setKeyboard(void) noexcept;
    void        setPosition(void);
    void        placeBomb(void);
    bool        isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir);
    bool        entitiesHere(const Vector3& pos) noexcept;
    KeyboardKey moveUp;
    KeyboardKey moveDown;
    KeyboardKey moveLeft;
    KeyboardKey moveRight;
    KeyboardKey dropBomb;
    int         id;
    GameData*   data;
    std::vector<std::unique_ptr<Entities>>* bombs;
    std::vector<ItemType>                   items;
    bool                                    wallpass;
    std::unique_ptr<Timer>                  wallpassTimer;
    bool                                    wallpassEnd;
};
