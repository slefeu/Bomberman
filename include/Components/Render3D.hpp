/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Render3D
*/

#ifndef RENDERER3D_HPP_
#define RENDERER3D_HPP_

#include <string>

#include "raylib.h"

#define MODEL model->get()

enum class ModelType { BOMB, WALL, CRATE };

class Render3D
{
  public:
    Model     model;
    Texture2D texture;

  public:
    Render3D(std::string path, std::string texturePath) noexcept;
    ~Render3D() noexcept;
};

#endif /* !RENDERER3D_HPP_ */
