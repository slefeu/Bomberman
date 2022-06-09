/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#include "GameData.hpp"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "Error.hpp"

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

void GameData::setEntities(std::vector<std::unique_ptr<Entity>>* entities) noexcept
{
    _entities = entities;
}

void GameData::updateMouse() noexcept
{
    mouse_.update();
}

MouseHandler GameData::getMouseHandler() const noexcept
{
    return (mouse_);
}

void GameData::setCurrentScene(const SceneType& scene) noexcept
{
    current_scene_ = scene;
}

SceneType GameData::getCurrentScene() const noexcept
{
    return (current_scene_);
}

std::string GameData::getCurrentDateTime(void) const noexcept
{
    char       currentTimeString[80];
    time_t     currentTime = time(0);
    struct tm* tstruct     = localtime(&currentTime);

    strftime(currentTimeString, sizeof(currentTimeString), "%Y-%m-%d.%X", tstruct);
    return currentTimeString;
}

void GameData::saveGame(void) const
{
    std::string   fileName = "Save/" + getCurrentDateTime();
    std::ofstream file(fileName);

    if (!file.is_open()) {
        std::filesystem::create_directory("Save");
        return saveGame();
    }
    std::cout << "Open" << std::endl;
    file << "save " << fileName << std::endl;
    file << nbPlayer << std::endl;
}
