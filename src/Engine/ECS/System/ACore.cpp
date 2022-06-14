/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** ICore
*/

#include "ACore.hpp"

Scene& ACore::findScene() noexcept
{
    return (*scenes[data_.getCurrentSceneIndex()]);
}

GameData& ACore::getData() noexcept
{
    return (data_);
}

const GameData& ACore::getData() const noexcept
{
    return (data_);
}

void ACore::setExit(bool value) noexcept
{
    exit_ = value;
}