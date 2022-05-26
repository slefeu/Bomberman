/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Model3D
*/

#pragma once

#include <string>

#include "raylib.h"

#define NEW_MODEL(obj, texture) std::make_unique<Model3D>(obj, texture)

class Model3D
{
  public:
    Model     model;
    Texture2D texture;

  public:
    Model3D(std::string path, std::string texturePath) noexcept;
    ~Model3D() noexcept;
};
