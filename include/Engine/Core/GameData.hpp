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
    ~GameData() noexcept                     = default;
    GameData(const GameData& other) noexcept = delete;
    GameData(GameData&& other) noexcept      = delete;
    GameData& operator=(const GameData& rhs) noexcept = delete;
    GameData& operator=(GameData&& rhs) noexcept = delete;

    Vector2   getMousePosition() const noexcept;
    void      updateMouse() noexcept;
    void      setCurrentScene(const SceneType& scene) noexcept;
    SceneType getCurrentScene() const noexcept;

  public:
    int   fps;
    int   winWidth;
    int   winHeight;
    int   nbPlayer;
    float timeParty;

  public:
    std::vector<std::unique_ptr<Model3D>> models;
    std::vector<std::unique_ptr<Sprite>>  sprites;
    std::vector<std::unique_ptr<Entity>>  players;

  protected:
  private:
    MouseHandler mouse_handler_;
    SceneType    current_scene_ = SceneType::MENU;
};