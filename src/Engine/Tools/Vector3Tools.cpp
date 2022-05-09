/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Vector3Tools
*/

#include "Vector3Tools.hpp"

Vector3 Vector3Tools::add(Vector3 v1, Vector3 v2) noexcept
{
    return (Vector3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector3 Vector3Tools::sub(Vector3 v1, Vector3 v2) noexcept
{
    return (Vector3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector3 Vector3Tools::mul(Vector3 v1, Vector3 v2) noexcept
{
    return (Vector3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
}

Vector3 Vector3Tools::div(Vector3 v1, Vector3 v2) noexcept
{
    return (Vector3){v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
}

Vector3 Vector3Tools::add(Vector3 v1, float v2) noexcept
{
    return (Vector3){v1.x + v2, v1.y + v2, v1.z + v2};
}

Vector3 Vector3Tools::sub(Vector3 v1, float v2) noexcept
{
    return (Vector3){v1.x - v2, v1.y - v2, v1.z - v2};
}

Vector3 Vector3Tools::mul(Vector3 v1, float v2) noexcept
{
    return (Vector3){v1.x * v2, v1.y * v2, v1.z * v2};
}

Vector3 Vector3Tools::div(Vector3 v1, float v2) noexcept
{
    return (Vector3){v1.x / v2, v1.y / v2, v1.z / v2};
}

bool Vector3Tools::equals(Vector3 v1, Vector3 v2) noexcept
{
    return (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z);
}