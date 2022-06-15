/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Parser
*/

#pragma once

#include <string>
#include <vector>

#include "Entity.hpp"
#include "Player.hpp"

class GameData;

class Save
{
  public:
    Save(GameData& data);
    ~Save() noexcept                          = default;
    Save(const Save& other) noexcept          = delete;
    Save(Save&& other) noexcept               = delete;
    Save& operator=(const Save& rhs) noexcept = delete;
    Save& operator=(Save&& rhs) noexcept      = delete;

    void load(const std::string& file);
    void save();

  private:
    void        loadGameData(std::vector<std::string> data);
    void        loadGamePlayerData(std::vector<std::string> data, int* index);
    void        loadGameBombData(std::vector<std::string> data, int* index);
    void        loadGameCrateData(std::vector<std::string> data, int* index);
    void        loadGameWallData(std::vector<std::string> data, int* index);
    void        writeDataGame(std::ofstream& file);
    void        writeDataPlayer(std::ofstream& file);
    void        writeDataCrate(std::ofstream& file);
    void        writeDataWall(std::ofstream& file);
    void        writeDataBombPlayer(std::ofstream& file, const std::unique_ptr<Entity>& bomb) const;
    std::string getCurrentDateTime() const noexcept;
    int         getNbBomb(
                const std::vector<std::unique_ptr<Entity>>& entities, const Player* player) const noexcept;
    void splitStr(std::string str, std::string delimiter, std::vector<std::string>* result) const;

  private:
    GameData& data;
};
