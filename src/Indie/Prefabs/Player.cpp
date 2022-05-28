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
#include "Error.hpp"

Player::Player(int newId, GameData* data)
    : Entities(EntityType::E_PLAYER)
    , nbBomb(1)
    , speed(2.0f)
    , bombSize(3)
    , id(newId)
    , data(data)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the player element.\n"));
    transform->get().setSize({ 0.5f, 0.5f, 0.5f });
    transform->get().setPosition(
        { 0.0f, 0.0f + (transform->get().getSize().y / 2), 2.0f });
    renderer->get().setRenderType(RenderType::R_CUBE);
    renderer->get().setColor(MAGENTA);
    setKeyboard();
    setPosition();
    addComponent(BoxCollider(
        transform->get().getPosition(), transform->get().getSize(), true));
}

void Player::Display()
{
    auto renderer  = getComponent<Render>();
    auto transform = getComponent<Transform3D>();
    if (!renderer.has_value() || !transform.has_value())
        throw(Error("Error in displaying the player element.\n"));
    if (!getEnabledValue()) return;
    renderer->get().display(transform->get());
}

void Player::Update()
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    if (!hitbox.has_value() || !transform.has_value())
        throw(Error("Error in updating the player element.\n"));
    if (!getEnabledValue()) return;

    hitbox->get().update(transform->get().getPosition());

    if (IsGamepadAvailable(id)) {
        // Mouvements au joystick
        float axisX = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_Y);

        if (axisY < -0.5f && !isCollidingNextTurn(*bombs, 0, -1))
            transform->get().moveZ(-speed);
        if (axisY > 0.5f && !isCollidingNextTurn(*bombs, 0, 1))
            transform->get().moveZ(speed);
        if (axisX < -0.5f && !isCollidingNextTurn(*bombs, -1, 0))
            transform->get().moveX(-speed);
        if (axisX > 0.5f && !isCollidingNextTurn(*bombs, 1, 0))
            transform->get().moveX(speed);
        if (IsGamepadButtonPressed(id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT))
            placeBomb();
    } else {
        // Mouvements au clavier
        if (IsKeyDown(moveUp) && !isCollidingNextTurn(*bombs, 0, -1))
            transform->get().moveZ(-speed);
        if (IsKeyDown(moveDown) && !isCollidingNextTurn(*bombs, 0, 1))
            transform->get().moveZ(speed);
        if (IsKeyDown(moveLeft) && !isCollidingNextTurn(*bombs, -1, 0))
            transform->get().moveX(-speed);
        if (IsKeyDown(moveRight) && !isCollidingNextTurn(*bombs, 1, 0))
            transform->get().moveX(speed);
        if (IsKeyPressed(dropBomb)) placeBomb();
    }
}

void Player::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_WALL) setEnabledValue(false);
    if (other->getEntityType() == EntityType::E_FIRE) {
        std::cout << "Player " << id << " has been killed" << std::endl;
        setEnabledValue(false);
    }
}

void Player::setPosition(void)
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value())
        throw(Error("Error in setting player position.\n"));
    switch (id) {
        case 0:
            transform->get().setX(-6.0f);
            transform->get().setZ(-4.0f);
            break;
        case 1:
            transform->get().setX(6.0f);
            transform->get().setZ(6.0f);

            break;
        case 2:
            transform->get().setX(6.0f);
            transform->get().setZ(-4.0f);
            break;
        case 3:
            transform->get().setX(-6.0f);
            transform->get().setZ(6.0f);
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

bool Player::isCollidingNextTurn(
    std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir)
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value())
        throw(Error("Error in updating the collision of the player.\n"));

    Vector3 position = transform->get().getPosition();
    Vector3 nextTurn = { position.x + (speed * xdir * GetFrameTime()),
        position.y,
        position.z + (speed * zdir * GetFrameTime()) };

    if (!getEnabledValue()) return false;
    for (auto& other : others) {
        if (hitbox == std::nullopt
            || other->getComponent<BoxCollider>() == std::nullopt)
            continue;
        auto other_hitbox = other->getComponent<BoxCollider>();
        if (other_hitbox.has_value()) {
            if (!hitbox->get().getIsSolid()
                || !other_hitbox->get().getIsSolid())
                continue;
            if (other_hitbox->get().isColliding(hitbox->get(), nextTurn)) {
                if (other->getEntityType() == EntityType::E_BOMB) return true;
                if (other->getEntityType() == EntityType::E_WALL) return true;
                if (other->getEntityType() == EntityType::E_CRATE) return true;
            }
        }
    }
    return false;
}

void Player::placeBomb()
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value())
        throw(Error("Error in updating the placement of bombs.\n"));
    if (nbBomb <= 0) return;
    nbBomb--;
    bombs->emplace_back(std::make_unique<Bomb>(transform->get().getPosition(),
        this,
        MODELS(M_BOMB),
        bombSize,
        data,
        bombs));
}

void Player::setBombArray(
    std::vector<std::unique_ptr<Entities>>* bombsArray) noexcept
{
    bombs = bombsArray;
}