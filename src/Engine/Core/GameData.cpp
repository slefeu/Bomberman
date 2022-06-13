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
#include <memory>
#include <vector>

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Entity.hpp"
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

std::string getCurrentDateTime(void) noexcept
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
    file << "save " << fileName << std::endl;
    file << nb_players_ << std::endl;
    writeDataPlayer(file);
    file << "Crates" << std::endl;
    writeDataCrate(file);
    file << "Walls" << std::endl;
    writeDataWall(file);
}

int getNbBomb(std::vector<std::unique_ptr<Entity>>* bombs, const Player* player)
{
    int nb = 0;

    for (auto& bomb : *bombs) {
        int  playerId = player->getId();
        auto bombN    = dynamic_cast<Bomb*>(bomb.get());
        if (!bombN) continue;
        int BombOwnerId = bombN->getOwnerId();
        if (!Type:: instanceof <Bomb>(bomb.get()) && BombOwnerId != playerId) continue;
        nb++;
    }
    return nb;
}

void GameData::writeDataPlayer(std::ofstream& file) const
{
    for (auto& player : players) {
        auto transform = player->getComponent<Transform3D>();

        if (!transform.has_value() || !Type:: instanceof <Player>(player.get())) continue;
        auto* tmp    = dynamic_cast<const Player*>(player.get());
        int   nbBomb = getNbBomb(tmp->getBombs(), tmp);
        // int  nbBombPlaced = int(tmp->getBombs()->size());
        file << "Player" << std::endl;
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
        if (nbBomb == 0) continue;
        file << nbBomb << std::endl;
        file << "Bombs" << std::endl;
        for (auto& bomb : *tmp->getBombs()) {
            auto bombN = dynamic_cast<Bomb*>(bomb.get());
            if (!bombN) continue;
            int bombOwnerId = bombN->getOwnerId();
            if (bombOwnerId != tmp->getId()) continue;
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

void splitStr(std::string str, std::string delimiter, std::vector<std::string>* result)
{
    size_t pos = 0;

    if (delimiter.empty()) { throw Error("invalid line: " + str + " " + delimiter); }

    (*result).clear();
    while ((pos = str.find(delimiter)) != std::string::npos) {
        (*result).push_back(str.substr(0, pos));
        str.erase(0, pos + delimiter.length());
    }
    (*result).push_back(str);
}

void GameData::loadGame(std::string fileName)
{
    std::ifstream            file(fileName);
    std::string              line;
    std::vector<std::string> data;

    if (!file.is_open()) throw Error("Cannot open file");
    while (std::getline(file, line, '\n')) { data.emplace_back(line); }
    loadGameData(data);
}

void GameData::loadGameData(std::vector<std::string> data)
{
    int index = 2;

    nbPlayer = std::stoi(data[1]);
    for (int i = 0; i < nbPlayer; i++) {
        if (data[index].find("Player") != 0) throw Error("Save not valid");
        loadGamePlayerData(data, &index);
        index++;
    }
    if (data[index].find("Crates") != 0) throw Error("Save not valid");
    while (!data[index].find("Walls")) {
        index++;
        loadGameCrateData(data, &index);
    }
    while (data[index] != data.back()) {
        index++;
        loadGameWallData(data, &index);
    }
}

void GameData::loadGamePlayerData(std::vector<std::string> data, int* index)
{
    int                      id;
    int                      type;
    int                      nbBombPlaced;
    Vector3D                 pos;
    std::vector<std::string> split;
    std::unique_ptr<Player>  player;

    id = std::stoi(data[*index]);

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    if (split.size() != 3) throw Error("Save not valid");
    pos.x  = std::stof(split[0]);
    pos.y  = std::stof(split[1]);
    pos.z  = std::stof(split[2]);
    player = std::make_unique<Player>(id, this);
    player->setPosition(pos);

    *index = *index + 1;
    type   = std::stoi(data[*index]);

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    if (split.size() != 3) throw Error("Save not valid");
    player->setSpeed(std::stoi(split[0]));
    player->setNbBomb(std::stoi(split[1]));
    player->setBombSize(std::stoi(split[2]));

    player->setPlayerType(static_cast<PlayerType>(type));
    _entities->emplace_back(player.get());

    *index       = *index + 1;
    nbBombPlaced = std::stoi(data[*index]);

    *index = *index + 1;
    if (nbBombPlaced > 0 && !data[*index].find("Bombs")) {
        for (int i = 0; i < nbBombPlaced; i++) {
            loadGameBombData(data, index);
            *index = *index + 1;
        }
    }
}

void GameData::loadGameBombData(std::vector<std::string> data, int* index)
{
    Player*                  player = dynamic_cast<Player*>(_entities->back().get());
    Vector3D                 pos;
    int                      lifeTime;
    std::vector<std::string> split;
    std::unique_ptr<Bomb>    bomb;

    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);

    *index   = *index + 1;
    lifeTime = std::stoi(data[*index]);
    bomb     = std::make_unique<Bomb>(pos,
        player,
        &models[static_cast<int>(ModelType::M_BOMB)],
        player->getBombSize(),
        this,
        player->getBombs());
    bomb->setLifeTime(lifeTime);
    player->getBombs()->emplace_back(bomb.get());
    _entities->emplace_back(bomb.get());
}

void GameData::loadGameCrateData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Crate>   crate;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stoi(split[0]);
    pos.y = std::stoi(split[1]);
    pos.z = std::stoi(split[2]);
    crate = std::make_unique<Crate>(
        pos, &models[static_cast<int>(ModelType::M_CRATE)], this, _entities);
    _entities->emplace_back(crate.get());
}

void GameData::loadGameWallData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Wall>    wall;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stoi(split[0]);
    pos.y = std::stoi(split[1]);
    pos.z = std::stoi(split[2]);
    wall  = std::make_unique<Wall>(pos, &models[static_cast<int>(ModelType::M_WALL)]);
    _entities->emplace_back(wall.get());
}
