/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#include "GameData.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Error.hpp"
#include "Fire.hpp"
#include "InstanceOf.hpp"
#include "Item.hpp"
#include "Player.hpp"
#include "Wall.hpp"

/**
 * This function returns the mouse position.
 *
 * @return The mouse position.
 */
Vector2D GameData::getMousePos() const noexcept
{
    return (mouse_.getMousePosition());
}

/**
 * It updates the mouse
 */
void GameData::updateMouse() noexcept
{
    mouse_.update();
}

/**
 * It returns a copy of the MouseHandler object.
 *
 * @return A reference to the mouse_ object.
 */
MouseHandler GameData::getMouseHandler() const noexcept
{
    return (mouse_);
}

/**
 * It sets the current scene to the scene passed in as a parameter
 *
 * @param scene The scene to set as the current scene.
 */
void GameData::setCurrentScene(const bomberman::SceneType& scene) noexcept
{
    current_scene_ = static_cast<typename std::underlying_type<bomberman::SceneType>::type>(scene);
}

/**
 * It creates a new model and adds it to the list of models
 *
 * @param model_path The path to the model file.
 * @param texture_path The path to the texture file.
 */
void GameData::addModel(
    const std::string_view& model_path, const std::string_view& texture_path) noexcept
{
    models_.emplace_back(std::make_unique<Model3D>(model_path, texture_path));
}

/**
 * It creates a new sprite, adds it to the sprites_ vector, and returns a reference to the new
 * sprite
 *
 * @param texture_path The path to the texture file.
 * @param scale The scale of the sprite.
 */
void GameData::addSprite(const std::string_view& texture_path, float scale) noexcept
{
    sprites_.emplace_back(std::make_unique<Sprite>(texture_path, 0, 0, scale));
}

/**
 * It creates a new player object and adds it to the players_ vector
 *
 * @param index The index of the player.
 */
void GameData::addPlayer(int index) noexcept
{
    players_.emplace_back(std::make_unique<Player>(index, *this));
}

/**
 * It creates a new item and adds it to the list of entities
 *
 * @param item The type of item to add.
 */
void GameData::addItem(bomberman::ItemType item) noexcept
{
    entities_.emplace_back(std::make_unique<Item>(*this, item));
}

/**
 * It creates a new item at the given position and adds it to the list of entities
 *
 * @param position The position of the item.
 */
void GameData::addItem(const Vector3D& position) noexcept
{
    entities_.emplace_back(std::make_unique<Item>(position, *this));
}

/**
 * It returns the number of players in the game
 *
 * @return The number of players in the game.
 */
int GameData::getNbPlayers() const noexcept
{
    return (nb_players_);
}

/**
 * It sets the number of players
 *
 * @param value The value to set the parameter to.
 */
void GameData::setNbPlayers(int value) noexcept
{
    nb_players_ = value;
}

/**
 * It creates a new crate at the given position and adds it to the list of entities
 *
 * @param position The position of the crate.
 */
void GameData::addCrate(Vector3D position) noexcept
{
    entities_.emplace_back(std::make_unique<Crate>(position,
        *models_[static_cast<typename std::underlying_type<bomberman::ModelType>::type>(
            bomberman::ModelType::M_CRATE)],
        *this));
}

/**
 * It creates a new wall entity and adds it to the list of entities
 *
 * @param position The position of the wall.
 */
void GameData::addWall(Vector3D position) noexcept
{
    entities_.emplace_back(std::make_unique<Wall>(position,
        *models_[static_cast<typename std::underlying_type<bomberman::ModelType>::type>(
            bomberman::ModelType::M_WALL)]));
}

/**
 * It adds a fire to the game
 *
 * @param fire The fire to add to the game.
 */
void GameData::addFire(std::unique_ptr<Fire> fire) noexcept
{
    entities_.push_back(std::move(fire));
}

/**
 * It creates a new bomb entity and adds it to the list of entities
 *
 * @param position The position of the bomb
 * @param player_ref A reference to the player that placed the bomb.
 * @param size the size of the bomb
 */
void GameData::addBomb(Vector3D position, Player& player_ref, int size) noexcept
{
    entities_.emplace_back(std::make_unique<Bomb>(position,
        player_ref,
        *models_[static_cast<typename std::underlying_type<bomberman::ModelType>::type>(
            bomberman::ModelType::M_BOMB)],
        size,
        *this));
}

/**
 * It returns a reference to the vector of unique pointers to Entity objects
 *
 * @return A reference to the vector of unique pointers to Entity objects.
 */
std::vector<std::unique_ptr<Entity>>& GameData::getPlayers() noexcept
{
    return (players_);
}

/**
 * It returns a reference to the vector of unique pointers to Model3D objects
 *
 * @return A reference to the vector of unique pointers to Model3D objects.
 */
std::vector<std::unique_ptr<Model3D>>& GameData::getModels() noexcept
{
    return (models_);
}

/**
 * It returns a reference to the vector of unique pointers to Sprite objects
 *
 * @return A reference to the sprites_ vector.
 */
std::vector<std::unique_ptr<Sprite>>& GameData::getSprites() noexcept
{
    return (sprites_);
}

/**
 * It clears the entities_ vector
 */
void GameData::clearEntities() noexcept
{
    entities_.clear();
}

/**
 * It returns a string containing the current date and time in the format "YYYY-MM-DD.HH:MM:SS"
 *
 * @return A string containing the current date and time.
 */
std::string getCurrentDateTime(void) noexcept
{
    char       currentTimeString[80];
    time_t     currentTime = time(0);
    struct tm* tstruct     = localtime(&currentTime);

    strftime(currentTimeString, sizeof(currentTimeString), "%Y-%m-%d.%X", tstruct);
    return currentTimeString;
}

/**
 * It creates a file with the current date and time as its name, then writes the number of players,
 * the players' data, the crates' data and the walls' data
 *
 * @return A string
 */
void GameData::saveGame(void)
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

/**
 * It counts the number of bombs that belong to a player
 *
 * @param entities a vector of all the entities in the game
 * @param player The player that we want to know the number of bombs for.
 *
 * @return The number of bombs that the player has placed.
 */
int getNbBomb(const std::vector<std::unique_ptr<Entity>>& entities, const Player* player)
{
    int nb = 0;

    for (auto& bomb : entities) {
        int  playerId = player->getId();
        auto bombN    = dynamic_cast<Bomb*>(bomb.get());
        if (!bombN) continue;
        int BombOwnerId = bombN->getOwnerId();
        std::cout << "BombOwnerId " << BombOwnerId << ", PlayerId " << playerId << std::endl;
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
void GameData::writeDataPlayer(std::ofstream& file)
{
    for (auto& player : players_) {
        auto transform = player->getComponent<Transform3D>();

        if (!transform.has_value() || !Type:: instanceof <Player>(player.get())) continue;
        auto* tmp    = dynamic_cast<const Player*>(player.get());
        int   nbBomb = getNbBomb(entities_, tmp);
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
        for (auto& bomb : entities_) {
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
void GameData::writeDataBombPlayer(std::ofstream& file, const std::unique_ptr<Entity>& bomb) const
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
void GameData::writeDataCrate(std::ofstream& file)
{
    for (auto& crate : entities_) {
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
void GameData::writeDataWall(std::ofstream& file)
{
    for (auto& wall : entities_) {
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

/**
 * It opens a file, reads the file line by line, and then passes the data to another function
 */
void GameData::loadGame()
{
    std::ifstream            file(try_to_load);
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
void GameData::loadGameData(std::vector<std::string> data)
{
    int index = 2;

    nb_players_ = std::stoi(data[1]);
    for (int i = 0; i < nb_players_; i++) {
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
    std::cout << "Load finish" << std::endl;
}

/**
 * It loads the player data from the save file
 *
 * @param data The vector of strings that contains the data of the save file.
 * @param index the index of the vector of strings that we are currently reading
 */
void GameData::loadGamePlayerData(std::vector<std::string> data, int* index)
{
    int                      id;
    int                      type;
    int                      nbBombPlaced;
    Vector3D                 pos;
    std::vector<std::string> split;

    *index = *index + 1;
    id     = std::stoi(data[*index]);

    addPlayer(id);
    auto* player = dynamic_cast<Player*>(players_.back().get());

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
void GameData::loadGameBombData(std::vector<std::string> data, int* index)
{
    Player*                  player = dynamic_cast<Player*>(players_.back().get());
    Vector3D                 pos;
    int                      lifeTime;
    std::vector<std::string> split;
    std::unique_ptr<Bomb>    bomb;

    *index = *index + 1;
    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);

    addBomb(pos, *player, player->getBombSize());
}

/**
 * It takes a vector of strings, and an index, and it adds a crate to the game world at the position
 * specified by the string at the index
 *
 * @param data The vector of strings that contains the data to be loaded.
 * @param index The index of the line in the file that is being read.
 */
void GameData::loadGameCrateData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Crate>   crate;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);
    addCrate(pos);
}

/**
 * It takes a vector of strings, and an index, and it adds a wall to the game world
 *
 * @param data The vector of strings that contains the data to be loaded.
 * @param index The index of the line in the file that is being read.
 */
void GameData::loadGameWallData(std::vector<std::string> data, int* index)
{
    std::vector<std::string> split;
    std::unique_ptr<Wall>    wall;
    Vector3D                 pos;

    splitStr(data[*index], ";", &split);
    pos.x = std::stof(split[0]);
    pos.y = std::stof(split[1]);
    pos.z = std::stof(split[2]);
    addWall(pos);
}

/**
 * It clears all the data containers
 */
void GameData::unloadAll() noexcept
{
    entities_.clear();
    players_.clear();
    models_.clear();
    sprites_.clear();
}

/**
 * It sets the value of the try_to_load member variable
 *
 * @param value The value to set the parameter to.
 */
void GameData::setTryToLoad(const std::string& value) noexcept
{
    try_to_load = value;
}

/**
 * It returns the string that is used to try to load the game data.
 *
 * @return The try_to_load variable.
 */
std::string GameData::tryToLoad() const noexcept
{
    return try_to_load;
}
