/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Wall
*/

#include "Wall.hpp"

Wall::Wall(Vector3 pos, std::unique_ptr<Render3D>* model) noexcept
    : Crate(pos, model)
{
    type = EntityType::E_WALL;
}