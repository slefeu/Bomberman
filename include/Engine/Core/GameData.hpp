/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/
#pragma once

#include "Entities.hpp"
#include "Model3D.hpp"

class GameData
{
  public:
    GameData(int fps, int winWidth, int winHeight, int nbPlayer) noexcept;
    ~GameData() noexcept                              = default;
    GameData(const GameData& other) noexcept          = delete;
    GameData(GameData&& other) noexcept               = delete;
    GameData& operator=(const GameData& rhs) noexcept = delete;
    GameData& operator=(GameData&& rhs) noexcept      = delete;

  public:
    int   fps;
    int   winWidth;
    int   winHeight;
    int   nbPlayer;
    int   currentScene;
    float timeParty;

  public:
    std::vector<std::unique_ptr<Model3D>>  models;
    std::vector<std::unique_ptr<Entities>> players;
};