/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Core
*/

#ifndef CORE_HPP_
#define CORE_HPP_

#include <memory>
#include <vector>

#include "Cameraman.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include "Settings.hpp"
class Core
{
  private:
    Cameraman                                  camera;
    std::vector<std::unique_ptr<Scene>>        scenes;
    int                                        currentScene;
    std::vector<std::unique_ptr<GameObject3D>> _players;
    std::vector<std::unique_ptr<Render3D>>     _models;
    Settings*                                  settings;

  public:
    Core(Settings* settings) noexcept;
    ~Core() noexcept = default;
    void run() noexcept;

  private:
    void switchScene(int scene) noexcept;
};

#endif /* !CORE_HPP_ */
