/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** GameData
*/

#include "GameData.hpp"

#include "Item.hpp"
#include "Player.hpp"

// void GameData::setEntities(
//     std::vector<std::unique_ptr<Entity>>* entities) noexcept
// {
//     entities_ = entities;
// }

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

int GameData::getNbPlayers() const noexcept
{
    return (nb_players_);
}

void GameData::setNbPlayers(int value) noexcept
{
    nb_players_ = value;
}

void GameData::addModel(
    const std::string_view& model_path, const std::string_view& texture_path) noexcept
{
    models_.emplace_back(std::make_unique<Model3D>(model_path, texture_path));
}

void GameData::addSprite(const std::string_view& texture_path) noexcept
{
    sprites_.emplace_back(std::make_unique<Sprite>(texture_path, 0, 0, 0.5f));
}

void GameData::addPlayer(int index) noexcept
{
    players_.emplace_back(std::make_unique<Player>(index, *this));
}

void GameData::addItem(bomberman::ItemType item) noexcept
{
    entities_.emplace_back(std::make_unique<Item>(*this, item));
}

std::vector<std::unique_ptr<Entity>>& GameData::getPlayers() noexcept
{
    return (players_);
}

std::vector<std::unique_ptr<Entity>>& GameData::getEntities() noexcept
{
    return (entities_);
}

std::vector<std::unique_ptr<Model3D>>& GameData::getModels() noexcept
{
    return (models_);
}

std::vector<std::unique_ptr<Sprite>>& GameData::getSprites() noexcept
{
    return (sprites_);
}

void GameData::clearEntities() noexcept
{
    entities_.clear();
}