/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#pragma once

#include "Entity.hpp"
#include "Model3D.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"

class GameData
{
  public:
    GameData(int fps, int winWidth, int winHeight, int nbPlayer) noexcept;
    GameData(const GameData& other) noexcept          = delete;
    GameData(GameData&& other) noexcept               = delete;
    GameData& operator=(const GameData& rhs) noexcept = delete;
    GameData& operator=(GameData&& rhs) noexcept      = delete;
    ~GameData() noexcept;

    MouseHandler getMouseHandler() const noexcept;
    void         updateMouse() noexcept;
    void         setCurrentScene(const SceneType& scene) noexcept;
    void         setEntities(std::vector<std::unique_ptr<Entity>>* entities) noexcept;
    void         saveGame(void) const;
    void         loadGame(void) noexcept;
    SceneType    getCurrentScene() const noexcept;

  private:
    std::string getCurrentDateTime(void) const noexcept;
    void        writeDataGame(std::ofstream& file) const;
    void        writeDataPlayer(std::ofstream& file) const;
    void        writeDataCrate(std::ofstream& file) const;
    void        writeDataWall(std::ofstream& file) const;
    void        writeDataBombPlayer(std::ofstream& file, const std::unique_ptr<Entity>& bomb) const;

  public:
    int   fps;
    int   winWidth;
    int   winHeight;
    int   nbPlayer;
    float timeParty;

  public:
    std::vector<std::unique_ptr<Model3D>> models;
    std::vector<std::unique_ptr<Entity>>* _entities;
    std::vector<std::unique_ptr<Sprite>>  sprites;
    std::vector<std::unique_ptr<Entity>>  players;

  private:
    MouseHandler mouse_;
    SceneType    current_scene_ = SceneType::MENU;
};
