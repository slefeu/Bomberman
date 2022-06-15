/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Parser
*/

#include "Save.hpp"

#include <filesystem>
#include <fstream>

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Player.hpp"
#include "Wall.hpp"

Save::Save(GameData& gdata)
    : data(gdata)
{
}

/**
 * It returns a string containing the current date and time in the format "YYYY-MM-DD.HH:MM:SS"
 *
 * @return A string containing the current date and time.
 */
std::string Save::getCurrentDateTime() const noexcept
{
    char       currentTimeString[80];
    time_t     currentTime = time(0);
    struct tm* tstruct     = localtime(&currentTime);

    strftime(currentTimeString, sizeof(currentTimeString), "%d.%m--%H:%M", tstruct);
    return currentTimeString;
}
/**
 * It creates a file with the current date and time as its name, then writes the number of players,
 * the players' data, the crates' data and the walls' data
 *
 * @return A string
 */
void Save::save()
{
    std::string   fileName = getCurrentDateTime();
    std::string   path     = "Save/" + fileName;
    std::ofstream file(path);

    if (!file.is_open()) {
        std::filesystem::create_directory("Save");
        return save();
    }
    file << "save " << fileName << std::endl;
    file << data.getNbPlayers() << std::endl;
    writeDataPlayer(file);
    file << "Crates" << std::endl;
    writeDataCrate(file);
    file << "Walls" << std::endl;
    writeDataWall(file);
}

/**
 * It counts the number of bombs that belong to a player
 *
 * @param entities a vector of all the entities in the game
 * @param player The player that we want to know the number of bombs for.
 *
 * @return The number of bombs that the player has placed.
 */
int Save::getNbBomb(
    const std::vector<std::unique_ptr<Entity>>& entities, const Player* player) const noexcept
{
    int nb = 0;

    for (auto& bomb : entities) {
        int  playerId = player->getId();
        auto bombN    = dynamic_cast<Bomb*>(bomb.get());
        if (!bombN) continue;
        int BombOwnerId = bombN->getOwnerId();
        if (!Type:: instanceof <Bomb>(bomb.get()) || BombOwnerId != playerId) continue;
        nb++;
    }
    return nb;
}

/**
 * It writes the player's data to the file
 *
 * @param file the file to write to
 */
void Save::writeDataPlayer(std::ofstream& file)
{
    for (auto& player : data.getPlayers()) {
        auto transform = player->getComponent<Transform3D>();

        if (!transform.has_value() || !Type:: instanceof <Player>(player.get())) continue;
        auto* tmp    = dynamic_cast<const Player*>(player.get());
        int   nbBomb = getNbBomb(data.getEntities(), tmp);
        file << "Player" << std::endl;
        /// Write Player Id/////////////////////////////////////////////////////
        file << tmp->getId() << std::endl;
        /// Write Player Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY() << ";"
             << transform->get().getPositionZ() << std::endl;
        /// Write Player Info///////////////////////////////////////////////////
        file << int(tmp->getType()) << std::endl;
        /// Write Player Stat///////////////////////////////////////////////////
        file << tmp->getSpeed() << ";" << tmp->getNbBomb() << ";" << tmp->getBombSize()
             << std::endl;
        /// Write Player Bot Boolean////////////////////////////////////////////
        file << ((tmp->isPlayer()) ? 0 : 1) << std::endl;
        /// Write Player Nb Bomb///////////////////////////////////////////////
        file << nbBomb << std::endl;
        if (nbBomb == 0) continue;
        file << "Bombs" << std::endl;
        for (auto& bomb : data.getEntities()) {
            auto bombN = dynamic_cast<Bomb*>(bomb.get());
            if (!bombN) continue;
            int bombOwnerId = bombN->getOwnerId();
            if (bombOwnerId != tmp->getId()) continue;
            writeDataBombPlayer(file, bomb);
        }
    }
}

/**
 * It writes the position of the bomb to the file
 *
 * @param file The file to write to.
 * @param bomb The bomb entity to write to the file.
 *
 * @return a reference to the file.
 */
void Save::writeDataBombPlayer(std::ofstream& file, const std::unique_ptr<Entity>& bomb) const
{
    auto transform = bomb->getComponent<Transform3D>();

    if (!transform.has_value()) return;
    /// Write Bomb Position///////////////////////////////////////////////
    file << transform->get().getPositionX() << ";" << transform->get().getPositionY() << ";"
         << transform->get().getPositionZ() << std::endl;
}

/**
 * It writes the position of all crates to the file
 *
 * @param file The file to write to.
 */
void Save::writeDataCrate(std::ofstream& file)
{
    for (auto& crate : data.getEntities()) {
        auto transform = crate->getComponent<Transform3D>();
        if (!transform.has_value() || !Type:: instanceof <Crate>(crate.get())) continue;
        /// Write Crate Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY() << ";"
             << transform->get().getPositionZ() << std::endl;
    }
}

/**
 * It writes the position of all the walls in the game to a file
 *
 * @param file The file to write to.
 */
void Save::writeDataWall(std::ofstream& file)
{
    for (auto& wall : data.getEntities()) {
        auto transform = wall->getComponent<Transform3D>();
        if (!transform.has_value() || !Type:: instanceof <Wall>(wall.get())) continue;
        /// Write Crate Position///////////////////////////////////////////////
        file << transform->get().getPositionX() << ";" << transform->get().getPositionY() << ";"
             << transform->get().getPositionZ() << std::endl;
    }
}

/**
 * It splits a string into a vector of strings, using a delimiter
 *
 * @param str the string to split
 * @param delimiter the string to split the string by
 * @param result a pointer to a vector of strings. This is where the result will be stored.
 */
void Save::splitStr(std::string str, std::string delimiter, std::vector<std::string>* result) const
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

/**
 * It opens a file, reads the file line by line, and then passes the data to another function
 */
void Save::load(const std::string& fileName)
{
    std::ifstream            file(fileName);
    std::string              line;
    std::vector<std::string> data;

    if (!file.is_open()) throw Error("Cannot open file");
    while (std::getline(file, line, '\n')) { data.emplace_back(line); }
    loadGameData(data);
}

/**
 * It loads the data from the file into the game
 *
 * @param data The vector of strings that contains the data to load
 */
void Save::loadGameData(std::vector<std::string> data)
{
    int index = 2;

    this->data.setNbPlayers(std::stoi(data[1]));
    for (int i = 0; i < this->data.getNbPlayers(); i++) {
        if (data[index].find("Player") != 0)
            throw Error("Save not valid: " + data[index] + " in loadGameData Player");
        loadGamePlayerData(data, &index);
    }

    if (data[index].find("Crates") != 0)
        throw Error("Save not valid: " + data[index] + " in loadGameData Crates");
    index++;
    while (data[index].find("Walls") != 0) {
        try {
            loadGameCrateData(data, &index);
        } catch (std::exception err) {
            throw Error("Save not valid: " + data[index] + " in loadGameCrate " + err.what());
        }
        index++;
    }

    if (data[index].find("Walls") != 0)
        throw Error("Save not valid: " + data[index] + " in loadGameData Walls");

    while (data[index] != data.back()) {
        index++;
        try {
            loadGameWallData(data, &index);
        } catch (std::exception err) {
            throw Error("Save not valid: " + data[index] + " in loadGameWall " + err.what());
        }
    }
}

/**
 * It loads the player data from the save file
 *
 * @param data The vector of strings that contains the data of the save file.
 * @param index the index of the vector of strings that we are currently reading
 */
void Save::loadGamePlayerData(std::vector<std::string> data, int* index)
{
    int                      id;
    int                      type;
    int                      nbBombPlaced;
    Vector3D                 pos;
    std::vector<std::string> split;

    *index = *index + 1;
    id     = std::stoi(data[*index]);

    this->data.addPlayer(id);
    auto* player = dynamic_cast<Player*>(this->data.getPlayers().back().get());

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    if (split.size() != 3) throw Error("Save not valid: " + data[*index] + " loadGamePlayer");
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);
    player->setPosition(pos);

    *index = *index + 1;
    type   = std::stoi(data[*index]);
    player->setPlayerType(static_cast<PlayerType>(type));

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    if (split.size() != 3) throw Error("Save not valid: " + data[*index] + " loadGamePlayer");
    player->setSpeed(std::stof(split[0]));
    player->setNbBomb(std::stoi(split[1]));
    player->setBombSize(std::stoi(split[2]));

    *index = *index + 1;
    player->setIsBot(std::stoi(data[*index]) == 1 ? true : false);

    *index       = *index + 1;
    nbBombPlaced = std::stoi(data[*index]);

    *index = *index + 1;
    if (nbBombPlaced > 0 && !data[*index].find("Bombs")) {
        for (int i = 0; i < nbBombPlaced; i++) {
            try {
                loadGameBombData(data, index);
            } catch (std::exception err) {
                throw Error("Save not valid: " + data[*index] + " loadGameBomb " + err.what());
            }
        }
        *index = *index + 1;
    }
}

/**
 * It loads a bomb from a file
 *
 * @param data The vector of strings containing the data to load.
 * @param index The index of the line in the file that we're currently reading.
 */
void Save::loadGameBombData(std::vector<std::string> data, int* index)
{
    Player*                  player = dynamic_cast<Player*>(this->data.getPlayers().back().get());
    Vector3D                 pos;
    int                      lifeTime;
    std::vector<std::string> split;
    std::unique_ptr<Bomb>    bomb;

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);

    this->data.addBomb(pos, *player, player->getBombSize());
}

/**
 * It takes a vector of strings, and an index, and it adds a crate to the game world at the position
 * specified by the string at the index
 *
 * @param data The vector of strings that contains the data to be loaded.
 * @param index The index of the line in the file that is being read.
 */
void Save::loadGameCrateData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Crate>   crate;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);
    this->data.addCrate(pos);
}

/**
 * It takes a vector of strings, and an index, and it adds a wall to the game world
 *
 * @param data The vector of strings that contains the data to be loaded.
 * @param index The index of the line in the file that is being read.
 */
void Save::loadGameWallData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Wall>    wall;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);
    this->data.addWall(pos);
}
