/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** MyCameraman.cpp
*/

#include "MyCameraman.hpp"

#include <math.h>

#include <cmath>

#include "Error.hpp"

void MyCameraman::lookBetweenEntity(const std::vector<std::unique_ptr<Entity>>& entities)
{
    float minX = INFINITY;
    float minZ = INFINITY;
    float maxX = -minX;
    float maxZ = -minZ;

    for (auto& entity : entities) {
        auto render = entity->getComponent<Render>();
        if (!render.has_value()) continue;

        auto transform = entity->getComponent<Transform3D>();
        if (!transform.has_value()) throw(Error("Error in camera_ handling.\n"));

        Vector3D pos = transform->get().getPosition();
        if (pos.x < minX) minX = pos.x;
        if (pos.x > maxX) maxX = pos.x;
        if (pos.z < minZ) minZ = pos.z;
        if (pos.z > maxZ) maxZ = pos.z;
    }

    float newX = (minX + maxX) / 2;
    float newZ = (minZ + maxZ) / 2;

    camera_.target.x   = newX;
    camera_.target.z   = newZ;
    camera_.position.x = newX;
    camera_.position.z = newZ + 2.0f;
}