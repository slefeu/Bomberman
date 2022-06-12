/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#pragma once

#include <memory>
#include <type_traits>
#include <vector>

#include "AudioDevice.hpp"
#include "GameData.hpp"
#include "MyCameraman.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include "Window.hpp"

class Core
{
  public:
    Core() noexcept;
    ~Core() noexcept;
    Core(const Core& other) noexcept          = delete;
    Core(Core&& other) noexcept               = delete;
    Core& operator=(const Core& rhs) noexcept = delete;
    Core& operator=(Core&& rhs) noexcept      = delete;

    void            run() noexcept;
    void            switchScene(const bomberman::SceneType& scene) noexcept;
    void            setExit(bool value) noexcept;
    WindowManager&  getWindow() noexcept;
    MyCameraman&    getCameraman() noexcept;
    GameData&       getData() noexcept;
    const GameData& getData() const noexcept;

  protected:
  private:
    // methods
    void   checkExit() noexcept;
    void   checkCamera() noexcept;
    Scene& findScene() noexcept;
    void   switchScene(const int& scene) noexcept;
    void   initGameModels() noexcept;
    void   initScenes() noexcept;
    void   initSprites() noexcept;

    // attributes
    bool        exit_ = false;
    MyCameraman camera_;

    GameData                            data_;
    std::unique_ptr<WindowManager>      window_;
    std::vector<std::unique_ptr<Scene>> scenes = {};
};
