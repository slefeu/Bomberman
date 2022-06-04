/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Model3D
*/

#include "Model3D.hpp"

Model3D::Model3D(std::string path, std::string texturePath) noexcept
    : model(LoadModel(path.c_str()))
    , texture(LoadTexture(texturePath.c_str()))
{
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
}

Model3D::~Model3D() noexcept
{
    UnloadTexture(texture);
    UnloadModel(model);

    if (!anims) return;

    for (unsigned int i = 0; i < animsCount; i++) UnloadModelAnimation(anims[i]);
    RL_FREE(anims);
}

void Model3D::addAnimation(std::string path) noexcept
{
    anims = LoadModelAnimations(path.c_str(), &animsCount);
}

void Model3D::updateAnimation() noexcept
{
    if (anims == nullptr) return;
    if (isAnimated) {
        animFrameCounter += 1.0f;
        UpdateModelAnimation(model, anims[0], animFrameCounter);
        if (animFrameCounter >= anims[0].frameCount) animFrameCounter = 0;
    }
}

void Model3D::resetAnimation(int frame) noexcept
{
    if (anims == nullptr) return;
    animFrameCounter = frame;
    UpdateModelAnimation(model, anims[0], animFrameCounter);
}