/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Enums
*/

#pragma once
#include <cstddef>

enum class EntityType {
    E_PLAYER,
    E_BOX,
    E_BOMB,
    E_CRATE,
    E_WALL,
    E_FIRE,
    E_ITEM
};

enum class ModelType {
    M_BOMB,
    M_WALL,
    M_CRATE,
    M_IROLLER,
    M_IBOMB,
    M_IFIRE,
    M_IWALL,
    M_NONE
};

enum class ComponentType { BOXCOLLIDER, RENDER, TRANSFORM };

#define MODEL model->get()
#define NEW_HITBOX(pos, size, isSolid) \
    std::make_unique<BoxCollider>(pos, size, isSolid);
#define NEW_WALL(pos)       \
    std::make_unique<Wall>( \
        pos, &data_->models[static_cast<int>(ModelType::M_WALL)])
#define NEW_CRATE(pos, data, Entity)                          \
    std::make_unique<Crate>((Vector3)pos,                     \
        &data_->models[static_cast<int>(ModelType::M_CRATE)], \
        data,                                                 \
        Entity)
