/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Models
*/

#ifndef MODELS_HPP_
#define MODELS_HPP_

#include <string>

#include "raylib.h"

class Models
{
  public:
    Model     model;
    Texture2D texture;

  public:
    Models(std::string path, std::string texturePath) noexcept;
    ~Models() noexcept;
};

#endif /* !MODELS_HPP_ */
