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

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Player.hpp"
#include "Transform3D.hpp"
#include "Wall.hpp"

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
    std::string   fileName = getCurrentDateTime();
    std::string   path     = "Save/" + fileName;
    std::ofstream file(path);

    if (!file.is_open()) {
        std::filesystem::create_directory("Save");
        return saveGame();
    }
    file << "save " << fileName << std::endl << nbPlayer << std::endl;
    file << "Players" << std::endl;
    writeDataPlayer(file);
    file << "Crates" << std::endl;
    writeDataCrate(file);
    file << "Wall" << std::endl;
    writeDataWall(file);
}

void GameData::writeDataPlayer(std::ofstream& file) const
{
    for (auto& player : players) {
        auto transform = player->getComponent<Transform3D>();

        if (!transform.has_value() || !Type:: instanceof <Player>(player.get())) continue;
        auto tmp = dynamic_cast<const Player*>(player.get());
        /// Write Player Id/////////////////////////////////////////////////////
        file << tmp->getId() << std::endl;
        /// Write Player Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY()
             << transform->get().getPositionZ() << std::endl;
        /// Write Player Info///////////////////////////////////////////////////
        file << int(tmp->getType()) << std::endl;
        // file << int(tmp->getType()) << ";" << tmp->getWallPass() << tmp->getWallPassEnd()
        //      << std::endl;
        /// Write Player Stat///////////////////////////////////////////////////
        file << tmp->getSpeed() << ";" << tmp->getNbBomb() << ";" << tmp->getBombSize()
             << std::endl;
        /// Write Player Stat Max///////////////////////////////////////////////
        file << tmp->getSpeedMax() << ";" << tmp->getNbBombMax() << ";" << tmp->getBombSizeMax()
             << std::endl;
        for (std::unique_ptr<Entity>& bomb : *tmp->getBombs()) {
            if (!Type:: instanceof <Bomb>(bomb.get())) continue;
            writeDataBombPlayer(file, bomb);
        }
    }
}

void GameData::writeDataBombPlayer(std::ofstream& file, const std::unique_ptr<Entity>& bomb) const
{
    auto transform = bomb->getComponent<Transform3D>();
    auto tmp       = dynamic_cast<const Bomb*>(bomb.get());

    if (!transform.has_value()) return;
    /// Write Bomb Position///////////////////////////////////////////////
    file << transform->get().getPositionX() << ";" << transform->get().getPositionY()
         << transform->get().getPositionZ() << std::endl;
    file << tmp->getLifeTime() << std::endl;
}

void GameData::writeDataCrate(std::ofstream& file) const
{
    for (auto& crate : *_entities) {
        auto transform = crate->getComponent<Transform3D>();
        if (!transform.has_value() || !Type:: instanceof <Crate>(crate.get())) continue;
        /// Write Crate Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY()
             << transform->get().getPositionZ() << std::endl;
    }
}

void GameData::writeDataWall(std::ofstream& file) const
{
    for (auto& wall : *_entities) {
        auto transform = wall->getComponent<Transform3D>();
        if (!transform.has_value() || !Type:: instanceof <Wall>(wall.get())) continue;
        /// Write Crate Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY()
             << transform->get().getPositionZ() << std::endl;
    }
}
