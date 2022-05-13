/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Render3D
*/

#include "Render3D.hpp"

#include <iostream>

Render3D::Render3D(std::string path, std::string texturePath) noexcept
    : model(LoadModel(path.c_str()))
    , texture(LoadTexture(texturePath.c_str()))
{
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Render3D::~Render3D() noexcept
{
    std::cout << "Render3D destructor" << std::endl;
    UnloadTexture(texture);
    UnloadModel(model);
}