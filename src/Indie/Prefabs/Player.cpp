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

Player::Player(int newId, GameData* data) noexcept
    : id(newId)
    , data(data)
    , nbBomb(1)
    , speed(2.0f)
    , bombSize(3)
{
    transform3d.setSize({ 0.5f, 0.5f, 0.5f });
    transform3d.setPosition({ 0.0f, 0.0f + (transform3d.getSize().y / 2), 2.0f });
    render.setRenderType(RenderType::R_CUBE);
    render.setColor(MAGENTA);
    setKeyboard();
    setPosition();

    hitbox = NEW_HITBOX(transform3d.getPosition(), transform3d.getSize(), true);
    type   = EntityType::E_PLAYER;
}

void Player::Display() noexcept
{
    if (!isEnable) return;

    render.display(transform3d);
}

void Player::Update() noexcept
{
    if (!isEnable) return;

    hitbox->update(transform3d.getPosition());

    if (IsGamepadAvailable(id)) {
        // Mouvements au joystick
        float axisX = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_Y);

        if (axisY < -0.5f && !isCollidingNextTurn(*bombs, 0, -1)) transform3d.moveZ(-speed);
        if (axisY > 0.5f && !isCollidingNextTurn(*bombs, 0, 1)) transform3d.moveZ(speed);
        if (axisX < -0.5f && !isCollidingNextTurn(*bombs, -1, 0)) transform3d.moveX(-speed);
        if (axisX > 0.5f && !isCollidingNextTurn(*bombs, 1, 0)) transform3d.moveX(speed);
        if (IsGamepadButtonPressed(id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) placeBomb();
    } else {
        // Mouvements au clavier
        if (IsKeyDown(moveUp) && !isCollidingNextTurn(*bombs, 0, -1)) transform3d.moveZ(-speed);
        if (IsKeyDown(moveDown) && !isCollidingNextTurn(*bombs, 0, 1)) transform3d.moveZ(speed);
        if (IsKeyDown(moveLeft) && !isCollidingNextTurn(*bombs, -1, 0)) transform3d.moveX(-speed);
        if (IsKeyDown(moveRight) && !isCollidingNextTurn(*bombs, 1, 0)) transform3d.moveX(speed);
        if (IsKeyPressed(dropBomb)) placeBomb();
    }
}

void Player::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_WALL) isEnable = false;
    if (other->type == EntityType::E_FIRE) {
        std::cout << "Player " << id << " has been killed" << std::endl;
        isEnable = false;
    }
}

void Player::setPosition(void) noexcept
{
    switch (id) {
        case 0:
            transform3d.setX(-6.0f);
            transform3d.setZ(-4.0f);
            break;
        case 1:
            transform3d.setX(6.0f);
            transform3d.setZ(6.0f);

            break;
        case 2:
            transform3d.setX(6.0f);
            transform3d.setZ(-4.0f);
            break;
        case 3:
            transform3d.setX(-6.0f);
            transform3d.setZ(6.0f);
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
            moveDown  = KEY_KP_5;
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

bool Player::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    Vector3 position = transform3d.getPosition();
    Vector3 nextTurn = { position.x + (speed * xdir * GetFrameTime()), position.y, position.z + (speed * zdir * GetFrameTime()) };

    if (!isEnable) return false;
    for (auto& other : others) {
        if (hitbox == nullptr || other->hitbox == nullptr) continue;
        if (!hitbox->isSolid || !other->hitbox->isSolid) continue;
        if (other->hitbox->isColliding(hitbox, nextTurn)) {
            if (other->type == EntityType::E_BOMB) return true;
            if (other->type == EntityType::E_WALL) return true;
            if (other->type == EntityType::E_CRATE) return true;
        }
    }
    return false;
}

void Player::placeBomb(void) noexcept
{
    if (nbBomb <= 0) return;
    nbBomb--;
    bombs->emplace_back(std::make_unique<Bomb>(transform3d.getPosition(), this, MODELS(M_BOMB), bombSize, data, bombs));
}

void Player::setBombArray(std::vector<std::unique_ptr<GameObject3D>>* bombsArray) noexcept
{
    bombs = bombsArray;
}