/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Model3D
*/

#pragma once

#include <string>

#include "raylib.h"

enum class ModelType {
    M_BOMB,
    M_WALL,
    M_CRATE,
    M_IROLLER,
    M_IBOMB,
    M_IFIRE,
    M_IWALL,
    M_FIRE,
    M_PLAYER_1,
    M_PLAYER_2,
    M_PLAYER_3,
    M_PLAYER_4,
    M_NONE
};

class Model3D
{
  public:
    Model           model;
    Texture2D       texture;
    ModelAnimation* anims            = nullptr;
    int             animFrameCounter = 0;
    unsigned int    animsCount       = 0;
    bool            isAnimated       = true;
    int             skipFrame        = 1;

  public:
    Model3D(std::string path, std::string texturePath) noexcept;
    ~Model3D() noexcept;
    Model3D(const Model3D& other) noexcept = delete;
    Model3D(Model3D&& other) noexcept      = delete;
    Model3D& operator=(const Model3D& rhs) noexcept = delete;
    Model3D& operator=(Model3D&& rhs) noexcept = delete;

    void addAnimation(std::string path) noexcept;
    void updateAnimation() noexcept;
    void resetAnimation(int frame) noexcept;
    void setSkipFrame(int frame) noexcept;
};
