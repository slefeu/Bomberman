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
    ~Core() noexcept = default;
    void run() noexcept;

  private:
    void switchScene(int scene) noexcept;
};

#endif /* !CORE_HPP_ */
