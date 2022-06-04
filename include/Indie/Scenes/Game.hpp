/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#pragma once

#include <math.h>

#include <memory>
#include <vector>

#include "Core.hpp"
#include "Entity.hpp"
#include "Model3D.hpp"
#include "Scene.hpp"
#include "Timer.hpp"
#include "Fps.hpp"

enum class Direction { UP, RIGHT, DOWN, LEFT };

class Game : public Scene
{
  public:
    Game(GameData* data, Core& core_ref) noexcept;
    ~Game() noexcept;
    Game(const Game& other) noexcept = delete;
    Game(Game&& other) noexcept      = delete;
    Game& operator=(const Game& rhs) noexcept = delete;
    Game& operator=(Game&& rhs) noexcept = delete;

    void         display3D() noexcept final;
    void         display2D() noexcept final;
    void         action(Cameraman& camera, Vector2 mouse_pos) noexcept final;
    void         DestroyPool() noexcept final;
    void         CollisionPool() noexcept final;
    void         playMusic() const noexcept final;
    MusicManager getMusicManager() const noexcept final;
    Vector3      getCameraPosition() const noexcept final;
    Vector3      getCameraTarget() const noexcept final;
    Vector3      getCameraUp() const noexcept final;
    void         resetCameraman(Cameraman& camera) noexcept final;
    void         drawBackground() const noexcept final{};
    ColorManager getBackgroundColor() const noexcept final;

  private:
    // methods
    void createMap() noexcept;
    void hurryUp() noexcept;

    // attributes
    GameData*                              data_;
    std::vector<std::unique_ptr<Entity>>   entities_;
    std::unique_ptr<Timer>                 chrono_;

    float lastTimeBlockPlace;
    bool  isHurry;
    int   nbBlockPlaced;
    int   x    = -6;
    int   z    = 7;
    int   maxX = 6;
    int   maxZ = 6;
    int   minX = -5;
    int   minZ = -4;

    Direction    direction = Direction::UP;
    MusicManager loop_music_;
    Vector3      camera_position_ = { 0.0f, 13.0f, 2.0f };
    Vector3      camera_target_   = { 0.0f, 0.0f, 1.0f };
    Vector3      camera_up_       = { 0.0f, 2.0f, 0.0f };
    Core&        core_entry_;
    float        HurryUpX;
    ColorManager background_color_;

    static const inline char* GAME_MUSIC = "assets/audios/Game.mp3";
};
