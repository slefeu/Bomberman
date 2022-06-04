/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#include "GameData.hpp"

GameData::GameData(int fps, int winWidth, int winHeight, int nbPlayer) noexcept
    : fps(fps)
    , winWidth(winWidth)
    , winHeight(winHeight)
    , nbPlayer(nbPlayer)
    , timeParty(120.0f)
{
}

GameData::~GameData() noexcept
{
    for (auto& it : sprites) { it->unload(); }
}

void GameData::updateMouse() noexcept
{
    mouse_handler_.update();
}

Vector2 GameData::getMousePosition() const noexcept
{
    return (mouse_handler_.getPosition());
}

void GameData::setCurrentScene(const SceneType& scene) noexcept
{
    current_scene_ = scene;
}

SceneType GameData::getCurrentScene() const noexcept
{
    return (current_scene_);
}
