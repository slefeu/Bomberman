/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** AData
*/

#include "AData.hpp"

int AData::getCurrentSceneIndex() const noexcept
{
    return (current_scene_);
}

int AData::getNbPlayers() const noexcept
{
    return (nb_players_);
}

void AData::setNbPlayers(int value) noexcept
{
    nb_players_ = value;
}

std::vector<std::unique_ptr<Entity>>& AData::getEntities() noexcept
{
    return (entities_);
}

void AData::clearEntities() noexcept
{
    entities_.clear();
}
