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

Player::Player(const int newId, GameData* data)
    : Entities(EntityType::E_PLAYER)
    , nbBomb(1)
    , speed(2.0f)
    , bombSize(3)
    , id(newId)
    , data(data)
    , wallpass(false)
    , wallpassTimer(NEW_TIMER(5.0f))
    , wallpassEnd(false)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the player element.\n"));
    transform->get().setSize({ 0.5f, 0.5f, 0.5f });
    transform->get().setPosition({ 0.0f, 0.0f + (transform->get().getSize().y / 2), 2.0f });
    renderer->get().setRenderType(RenderType::R_CUBE);
    renderer->get().setColor(MAGENTA);
    setKeyboard();
    setPosition();
    addComponent(BoxCollider(transform->get().getPosition(), transform->get().getSize(), true));
}

void Player::Display()
{
    auto renderer  = getComponent<Render>();
    auto transform = getComponent<Transform3D>();
    if (!renderer.has_value() || !transform.has_value()) throw(Error("Error in displaying the player element.\n"));
    if (!getEnabledValue()) return;
    renderer->get().display(transform->get());
}

void Player::Update()
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    if (!hitbox.has_value() || !transform.has_value()) throw(Error("Error in updating the player element.\n"));
    if (!getEnabledValue()) return;

    hitbox->get().update(transform->get().getPosition());

    if (wallpass) {
        wallpassTimer->updateTimer();
        if (wallpassTimer->timerDone()) {
            wallpass    = false;
            wallpassEnd = true;
            wallpassTimer->resetTimer();
        }
    }

    if (IsGamepadAvailable(id)) {
        std::cout << "Gamepad " << id << " is available" << std::endl;
        // Mouvements au joystick
        float axisX = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_X);
        float axisY = GetGamepadAxisMovement(id, GAMEPAD_AXIS_LEFT_Y);

        if (axisY < -0.5f && !isCollidingNextTurn(*bombs, 0, -1)) transform->get().moveZ(-speed);
        if (axisY > 0.5f && !isCollidingNextTurn(*bombs, 0, 1)) transform->get().moveZ(speed);
        if (axisX < -0.5f && !isCollidingNextTurn(*bombs, -1, 0)) transform->get().moveX(-speed);
        if (axisX > 0.5f && !isCollidingNextTurn(*bombs, 1, 0)) transform->get().moveX(speed);
        if (IsGamepadButtonPressed(id, GAMEPAD_BUTTON_RIGHT_FACE_RIGHT)) placeBomb();
    } else {
        // Mouvements au clavier
        if (IsKeyDown(moveUp) && !isCollidingNextTurn(*bombs, 0, -1)) transform->get().moveZ(-speed);
        if (IsKeyDown(moveDown) && !isCollidingNextTurn(*bombs, 0, 1)) transform->get().moveZ(speed);
        if (IsKeyDown(moveLeft) && !isCollidingNextTurn(*bombs, -1, 0)) transform->get().moveX(-speed);
        if (IsKeyDown(moveRight) && !isCollidingNextTurn(*bombs, 1, 0)) transform->get().moveX(speed);
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
    if (!transform.has_value()) throw(Error("Error in setting player position.\n"));
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

bool Player::isCollidingNextTurn(std::vector<std::unique_ptr<Entities>>& others, int xdir, int zdir)
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value() || !hitbox.has_value())
        throw(Error("Error in updating the collision of the player.\n"));

    Vector3 position = transform->get().getPosition();
    Vector3 nextTurn = {
        position.x + (speed * xdir * GetFrameTime()), position.y, position.z + (speed * zdir * GetFrameTime())
    };

    if (!getEnabledValue()) return false;
    for (auto& other : others) {
        if (hitbox == std::nullopt || other->getComponent<BoxCollider>() == std::nullopt) continue;
        auto other_hitbox = other->getComponent<BoxCollider>();
        if (other_hitbox.has_value()) {
            if (!hitbox->get().getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
            if (other_hitbox->get().isColliding(hitbox->get(), nextTurn)) {
                if (other->getEntityType() == EntityType::E_BOMB) return true;
                if (other->getEntityType() == EntityType::E_WALL) return true;
                if (other->getEntityType() == EntityType::E_CRATE) {
                    if (wallpass) return false;
                    if (!wallpass && wallpassEnd) return false;
                    return true;
                }
            }
        }
    }
    if (wallpassEnd) {
        wallpassEnd = false;
        renderer->get().setColor(MAGENTA);
    }
    return false;
}

void Player::placeBomb()
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value()) throw(Error("Error in updating the placement of bombs.\n"));
    for (auto& i : *bombs) {
        auto bomb = i->getComponent<Transform3D>();
        if (bomb.has_value() && bomb->get().getPosition().x == round(transform->get().getPosition().x)
            && bomb->get().getPosition().z == round(transform->get().getPosition().z))
            return;
    }
    if (nbBomb <= 0) return;
    nbBomb--;
    bombs->emplace_back(
        std::make_unique<Bomb>(transform->get().getPosition(), this, MODELS(M_BOMB), bombSize, data, bombs));
}

void Player::setBombArray(std::vector<std::unique_ptr<Entities>>* bombsArray) noexcept
{
    bombs = bombsArray;
}

void Player::setWallPass(const bool& pass)
{
    // change te color of the player
    auto renderer = getComponent<Render>();
    if (!renderer.has_value()) throw(Error("Error in setting the wall pass.\n"));

    renderer->get().setColor(BLUE);

    wallpass = pass;
}

void Player::addItem(ItemType itemType)
{
    items.emplace_back(itemType);
}

void Player::dispatchItem(void) noexcept
{
    Vector3 pos;
    int     x;
    int     z;

    std::cout << "dispatch item" << std::endl;
    for (auto& item : items) {
        do {
            x   = rand() % 12 - 6;
            z   = rand() % 12 - 6;
            pos = { x * 1.0f, 0.01f, z * 1.0f };
        } while (!entitiesHere(pos));
        std::cout << "Item from Player drop at x:" << pos.x << " z:" << pos.z << std::endl;
        data->_entities->emplace_back(std::make_unique<Item>(pos, data, item));
    }
    items.clear();
}

bool Player::entitiesHere(const Vector3& pos) noexcept
{
    for (auto& entity : *data->_entities) {
        auto transform = entity->getComponent<Transform3D>();
        if (pos.x == transform->get().getPositionX() && pos.z == transform->get().getPositionZ()) return true;
    }
    return false;
}
