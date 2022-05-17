/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#ifndef GAMEDATA_HPP_
#define GAMEDATA_HPP_

#include "GameObject3D.hpp"
#include "Render3D.hpp"

class GameData
{
  public:
    GameData(int fps, int winWidth, int winHeight, int nbPlayer) noexcept;
    ~GameData() noexcept = default;

  public:
    int fps;
    int winWidth;
    int winHeight;
    int nbPlayer;
    int currentScene;

  public:
    std::vector<std::unique_ptr<Render3D>>      models;
    std::vector<std::unique_ptr<GameObject3D>>  players;
    std::vector<std::unique_ptr<GameObject3D>>* items;
};

#endif /* !GAMEDATA_HPP_ */
