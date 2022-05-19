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
    , currentScene(1)
    , timeParty(120.0f)
    , items(nullptr)
{
}
