/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#include "Player.hpp"

#include <iostream>

Player::Player(Vector3 pos, Vector3 newSize, Color newColor, int newId) noexcept
{
    position = pos;
    size     = newSize;
    position.y += (size.y / 2);
    color     = newColor;
    id        = newId;
    isSolid   = true;
    isTrigger = false;
    type      = EntityType::PLAYER;
    speed     = 0.1f;
    setKeyboard();
}

Player::Player(int newId, Color newColor) noexcept
{
    size      = { 0.5f, 0.5f, 0.5f };
    position  = { 0.0f, 0.0f + (size.y / 2), 2.0f };
    color     = newColor;
    id        = newId;
    isSolid   = true;
    isTrigger = false;
    speed     = 0.1f;
    type      = EntityType::PLAYER;
    setKeyboard();
}

void Player::setKeyboard(void) noexcept
{
    switch (id) {
        case 0:
            moveUp    = KEY_W;
            moveDown  = KEY_S;
            moveLeft  = KEY_A;
            moveRight = KEY_D;
            break;
        case 1:
            moveUp    = KEY_KP_8;
            moveDown  = KEY_KP_2;
            moveLeft  = KEY_KP_4;
            moveRight = KEY_KP_6;
            break;
        case 2:
            moveUp    = KEY_T;
            moveDown  = KEY_G;
            moveLeft  = KEY_F;
            moveRight = KEY_H;
            break;
        case 3:
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
    DrawCubeWiresV(position, size, BLACK);
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

void Player::action(std::vector<std::unique_ptr<Entities>>& others) noexcept
{
    if (IsGamepadAvailable(id)) {
        // Mouvements au joystick
        float axisX = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_Y);

        if (axisY > 0.5f && !isCollidingNextTurn(others, 0, 1)) moveZ(speed);
        if (axisY < -0.5f && !isCollidingNextTurn(others, 0, -1)) moveZ(-speed);
        if (axisX > 0.5f && !isCollidingNextTurn(others, 1, 0)) moveX(speed);
        if (axisX < -0.5f && !isCollidingNextTurn(others, -1, 0)) moveX(-speed);
    } else {
        // Mouvements au clavier
        if (IsKeyDown(moveUp) && !isCollidingNextTurn(others, 0, -1)) moveZ(-speed);
        if (IsKeyDown(moveDown) && !isCollidingNextTurn(others, 0, 1)) moveZ(speed);
        if (IsKeyDown(moveLeft) && !isCollidingNextTurn(others, -1, 0)) moveX(-speed);
        if (IsKeyDown(moveRight) && !isCollidingNextTurn(others, 1, 0)) moveX(speed);
    }
}

Vector3 Player::getPosition() noexcept
{
    return position;
}

Vector3 Player::getSize() noexcept
{
    return size;
}

bool Player::isColliding(std::vector<std::unique_ptr<Entities>>& others, Vector3& pos) noexcept
{
    for (auto& other : others) {
        if (other->isSolid && other->type != EntityType::PLAYER) {
            Vector3 otherPos  = other->getPosition();
            Vector3 otherSize = other->getSize();

            Vector3 BoundingBox1_1 = { pos.x - size.x / 2, pos.y - size.y / 2, pos.z - size.z / 2 };
            Vector3 BoundingBox1_2 = { pos.x + size.x / 2, pos.y + size.y / 2, pos.z + size.z / 2 };
            Vector3 BoundingBox2_1 = { otherPos.x - otherSize.x / 2, otherPos.y - otherSize.y / 2, otherPos.z - otherSize.z / 2 };
            Vector3 BoundingBox2_2 = { otherPos.x + otherSize.x / 2, otherPos.y + otherSize.y / 2, otherPos.z + otherSize.z / 2 };

            BoundingBox BoundingBox1 = { BoundingBox1_1, BoundingBox1_2 };
            BoundingBox BoundingBox2 = { BoundingBox2_1, BoundingBox2_2 };

            if (CheckCollisionBoxes(BoundingBox1, BoundingBox2)) return true;
        }
    }
    return false;
}

bool Player::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir) noexcept
{
    Vector3 nextTurn = { position.x + (speed * xdir), position.y, position.z + (speed * zdir) };
    return isColliding(others, nextTurn);
}