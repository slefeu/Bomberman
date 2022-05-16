/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#include "Player.hpp"

#include <iostream>

#include "Bomb.hpp"
#include "Collision.hpp"

Player::Player(int newId, Color newColor, std::vector<std::unique_ptr<GameObject3D>>* bombsArray, GameData* data) noexcept
    : id(newId)
    , data(data)
    , bombs(bombsArray)
    , nbBomb(3)
    , speed(3.0f)
    , bombSize(1)
{
    size     = { 0.5f, 0.5f, 0.5f };
    position = { 0.0f, 0.0f + (size.y / 2), 2.0f };
    hitbox   = std::make_unique<BoxCollider>(position, size, true);
    color    = newColor;
    type     = EntityType::E_PLAYER;
    setKeyboard();
    setPosition();
}

void Player::setPosition(void) noexcept
{
    switch (id) {
        case 0:
            position.x = -6.0f;
            position.z = -4.0f;
            break;
        case 1:
            position.x = 6.0f;
            position.z = -4.0f;
            break;
        case 2:
            position.x = -6.0f;
            position.z = 6.0f;
            break;
        case 3:
            position.x = 6.0f;
            position.z = 6.0f;
            break;
        default: break;
    }
}

void Player::setKeyboard(void) noexcept
{
    switch (id) {
        case 0:
            moveUp    = KEY_W;
            moveDown  = KEY_S;
            moveLeft  = KEY_A;
            moveRight = KEY_D;
            dropBomb  = KEY_Q;
            break;
        case 1:
            moveUp    = KEY_KP_8;
            moveDown  = KEY_KP_2;
            moveLeft  = KEY_KP_4;
            moveRight = KEY_KP_6;
            dropBomb  = KEY_KP_7;
            break;
        case 2:
            moveUp    = KEY_T;
            moveDown  = KEY_G;
            moveLeft  = KEY_F;
            moveRight = KEY_H;
            dropBomb  = KEY_R;
            break;
        case 3:
            moveUp    = KEY_I;
            moveDown  = KEY_K;
            moveLeft  = KEY_J;
            moveRight = KEY_L;
            dropBomb  = KEY_U;
            break;
        default: break;
    }
}

void Player::display() noexcept
{
    if (!isEnable) return;
    DrawCubeV(position, size, color);
    DrawCubeWiresV(position, size, BLACK);
    hitbox->update(position);
    hitbox->display();
}

void Player::moveX(float x) noexcept
{
    position.x += x * GetFrameTime();
}

void Player::moveY(float y) noexcept
{
    position.y += y * GetFrameTime();
}

void Player::moveZ(float z) noexcept
{
    position.z += z * GetFrameTime();
}

void Player::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    if (!isEnable) return;
    if (IsGamepadAvailable(id)) {
        // Mouvements au joystick
        float axisX = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_Y);

        if (axisY > 0.5f && !isCollidingNextTurn(others, 0, 1)) moveZ(speed);
        if (axisY < -0.5f && !isCollidingNextTurn(others, 0, -1)) moveZ(-speed);
        if (axisX > 0.5f && !isCollidingNextTurn(others, 1, 0)) moveX(speed);
        if (axisX < -0.5f && !isCollidingNextTurn(others, -1, 0)) moveX(-speed);

        if (IsGamepadButtonPressed(id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) placeBomb();
    } else {
        // Mouvements au clavier
        if (IsKeyDown(moveUp) && !isCollidingNextTurn(others, 0, -1)) moveZ(-speed);
        if (IsKeyDown(moveDown) && !isCollidingNextTurn(others, 0, 1)) moveZ(speed);
        if (IsKeyDown(moveLeft) && !isCollidingNextTurn(others, -1, 0)) moveX(-speed);
        if (IsKeyDown(moveRight) && !isCollidingNextTurn(others, 1, 0)) moveX(speed);
        if (IsKeyPressed(dropBomb)) placeBomb();
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

bool Player::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    if (!isEnable) return false;
    for (auto& other : others) {
        if (hitbox == nullptr || other->hitbox == nullptr) continue;
        if (!hitbox->isSolid || !other->hitbox->isSolid) continue;
        if (hitbox->isColliding(other->hitbox)) return true;
    }
    return false;
}

bool Player::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    Vector3 nextTurn = { position.x + (speed * xdir * GetFrameTime()), position.y, position.z + (speed * zdir * GetFrameTime()) };

    if (!isEnable) return false;
    for (auto& other : others) {
        if (hitbox == nullptr || other->hitbox == nullptr) continue;
        if (!hitbox->isSolid || !other->hitbox->isSolid) continue;
        if (other->hitbox->isColliding(hitbox, nextTurn)) return true;
    }
    return false;
}

void Player::placeBomb(void) noexcept
{
    if (nbBomb <= 0) return;
    nbBomb--;
    bombs->emplace_back(std::make_unique<Bomb>(position, this, MODELS(M_BOMB), bombSize));
}

void Player::setStats(int bomb, int sp, int size) noexcept
{
    nbBomb += bomb;
    speed += (float)sp;
    bombSize += size;
}

bool Player::update(void) noexcept
{
    return false;
}

bool Player::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}
