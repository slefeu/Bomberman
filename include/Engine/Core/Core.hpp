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
  private:
    Cameraman                           camera;
    std::vector<std::unique_ptr<Scene>> scenes;
    GameData*                           data;

  public:
    Core(GameData* data) noexcept;
    ~Core() noexcept                          = default;
    Core(const Core& other) noexcept          = delete;
    Core(Core&& other) noexcept               = delete;
    Core& operator=(const Core& rhs) noexcept = delete;
    Core& operator=(Core&& rhs) noexcept      = delete;

    void run() noexcept;

  private:
    void switchScene(const int& scene) noexcept;
};
