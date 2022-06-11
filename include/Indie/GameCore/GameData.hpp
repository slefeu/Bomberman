/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#pragma once

#include "Bomberman.hpp"
#include "Entity.hpp"
#include "Model3D.hpp"
#include "Mouse.hpp"
#include "Scene.hpp"
#include "Sprite.hpp"

class Fire;
class Player;

class GameData
{
  public:
    GameData() noexcept                      = default;
    GameData(const GameData& other) noexcept = delete;
    GameData(GameData&& other) noexcept      = delete;
    ~GameData() noexcept                     = default;

    GameData& operator=(const GameData& rhs) noexcept = delete;
    GameData& operator=(GameData&& rhs) noexcept = delete;

    Vector2D             getMousePos() const noexcept;
    void                 updateMouse() noexcept;
    void                 setCurrentScene(const bomberman::SceneType& scene) noexcept;
    bomberman::SceneType getCurrentScene() const noexcept;
    MouseHandler         getMouseHandler() const noexcept;
    int                  getNbPlayers() const noexcept;
    void                 setNbPlayers(int value) noexcept;
    void                 addModel(
                        const std::string_view& model_path, const std::string_view& texture_path) noexcept;
    void addSprite(const std::string_view& texture_path) noexcept;
    void addPlayer(int index) noexcept;
    void addItem(bomberman::ItemType item) noexcept;
    void addItem(const Vector3D& position) noexcept;
    void addCrate(Vector3D position) noexcept;
    void addWall(Vector3D position) noexcept;
    void addFire(std::unique_ptr<Fire> fire) noexcept;
    void addBomb(Vector3D position, Player& ref, int size) noexcept;
    void clearEntities() noexcept;

    std::vector<std::unique_ptr<Entity>>&  getPlayers() noexcept;
    std::vector<std::unique_ptr<Entity>>&  getEntities() noexcept;
    std::vector<std::unique_ptr<Model3D>>& getModels() noexcept;
    std::vector<std::unique_ptr<Sprite>>&  getSprites() noexcept;

  protected:
  private:
    MouseHandler         mouse_;
    bomberman::SceneType current_scene_ = bomberman::SceneType::MENU;
    int                  nb_players_    = 0;

    std::vector<std::unique_ptr<Model3D>> models_;
    std::vector<std::unique_ptr<Entity>>  entities_;
    std::vector<std::unique_ptr<Sprite>>  sprites_;
    std::vector<std::unique_ptr<Entity>>  players_;
};
