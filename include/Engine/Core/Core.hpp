/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#pragma once

#include <memory>
#include <vector>

#include "Cameraman.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Scene.hpp"

class Core
{
  public:
    Core(GameData* data) noexcept;
    ~Core() noexcept                 = default;
    Core(const Core& other) noexcept = delete;
    Core(Core&& other) noexcept      = delete;
    Core& operator=(const Core& rhs) noexcept = delete;
    Core& operator=(Core&& rhs) noexcept = delete;

    void run() noexcept;
    void switchScene(const SceneType& scene) noexcept;

  private:
    // methods
    void   closeElements() noexcept;
    bool   WindowIsOpened() const noexcept;
    void   UpdateLoopingMusic() noexcept;
    Scene& findScene() noexcept;

    // attributes
    Cameraman                           camera;
    std::vector<std::unique_ptr<Scene>> scenes;
    GameData*                           data;
};
