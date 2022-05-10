/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#include "Player.hpp"

Player::Player(int newId) noexcept
{
    position = { 0.0f, 1.0f, 2.0f };
    size     = { 1.0f, 2.0f, 1.0f };
    color    = GREEN;
    id       = newId;
    setKeyboard();
}

Player::Player(Vector3 pos, Vector3 newSize, Color newColor, int newId) noexcept
{
    position = pos;
    size     = newSize;
    color    = newColor;
    id       = newId;
    setKeyboard();
}

Player::Player(int newId, Color newColor) noexcept
{
    position = { 0.0f, 1.0f, 2.0f };
    size     = { 1.0f, 2.0f, 1.0f };
    color    = newColor;
    id       = newId;
    setKeyboard();
}

void Player::setKeyboard(void) noexcept
{
    switch (id) {
        case 1:
            moveUp    = KEY_W;
            moveDown  = KEY_S;
            moveLeft  = KEY_A;
            moveRight = KEY_D;
            break;
        case 2:
            moveUp    = KEY_KP_8;
            moveDown  = KEY_KP_2;
            moveLeft  = KEY_KP_4;
            moveRight = KEY_KP_6;
            break;
        case 3:
            moveUp    = KEY_T;
            moveDown  = KEY_G;
            moveLeft  = KEY_F;
            moveRight = KEY_H;
            break;
        case 4:
            moveUp    = KEY_I;
            moveDown  = KEY_K;
            moveLeft  = KEY_J;
            moveRight = KEY_L;
            break;
        default: break;
    }
}

void Player::display() noexcept
{
    DrawCubeV(position, size, color);
}

void Player::moveX(float x) noexcept
{
    position.x += x;
}

void Player::moveY(float y) noexcept
{
    position.y += y;
}

void Player::moveZ(float z) noexcept
{
    position.z += z;
}

void Player::action(void) noexcept
{
    if (IsKeyDown(moveUp)) moveZ(-0.1f);
    if (IsKeyDown(moveDown)) moveZ(0.1f);
    if (IsKeyDown(moveLeft)) moveX(-0.1f);
    if (IsKeyDown(moveRight)) moveX(0.1f);
}
