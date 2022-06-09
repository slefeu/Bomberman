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

void GameData::setEntities(std::vector<std::unique_ptr<Entity>>* entities) noexcept
{
    _entities = entities;
}

Vector2D GameData::getMousePos() const noexcept
{
    return (mouse_.getMousePosition());
}

void GameData::updateMouse() noexcept
{
    mouse_.update();
}

MouseHandler GameData::getMouseHandler() const noexcept
{
    return (mouse_);
}

void GameData::setCurrentScene(const bomberman::SceneType& scene) noexcept
{
    current_scene_ = scene;
}

bomberman::SceneType GameData::getCurrentScene() const noexcept
{
    return (current_scene_);
}
