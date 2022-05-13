/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Models
*/

#include "Models.hpp"

Models::Models(std::string path, std::string texturePath) noexcept
{
    model   = LoadModel(path.c_str());
    texture = LoadTexture(texturePath.c_str());

    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Models::~Models() noexcept
{
    UnloadTexture(texture);
    UnloadModel(model);
}
