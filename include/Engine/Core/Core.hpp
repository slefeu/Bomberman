/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#pragma once

#include <memory>
#include <vector>

#include "AudioDevice.hpp"
#include "Cameraman.hpp"
#include "GameData.hpp"
#include "Player.hpp"
#include "Scene.hpp"

class Core
{
  public:
    Core(GameData* data) noexcept;
    ~Core() noexcept                          = default;
    Core(const Core& other) noexcept          = delete;
    Core(Core&& other) noexcept               = delete;
    Core& operator=(const Core& rhs) noexcept = delete;
    Core& operator=(Core&& rhs) noexcept      = delete;

    void run() noexcept;
    void switchScene(const SceneType& scene) noexcept;
    void setExit(bool value) noexcept;

  protected:
  private:
    // methods
    void   checkExit() noexcept;
    Scene& findScene() noexcept;

    // attributes
    AudioDevice                         audio_;
    Cameraman                           camera;
    std::vector<std::unique_ptr<Scene>> scenes;
    GameData*                           data;
    bool                                exit_;
    void                                switchScene(const int& scene) noexcept;
    void                                createWindow() noexcept;
    void                                resetData() noexcept;
};
