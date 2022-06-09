/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Player
*/

#include "Player.hpp"

#include "Bomb.hpp"
#include "Error.hpp"
#include "Fire.hpp"
#include "InstanceOf.hpp"
#include "Item.hpp"
#include "Transform3D.hpp"
#include "Wall.hpp"

Player::Player(const int newId, GameData* data)
    : Entity()
    , id(newId)
    , data(data)
    , wallpass(false)
    , wallpassTimer(std::make_unique<Timer>(5.0f))
    , wallpassEnd(false)
    , killSound_(KILL)
{
    addComponent(Transform3D());
    addComponent(Render());
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the player element.\n"));
    transform->get().setSize({ 0.5f, 0.5f, 0.5f });
    transform->get().setPosition({ 0.0f, 0.0f + (transform->get().getSize().y / 2), 2.0f });
    transform->get().setRotationAxis({ 0.0f, 1.0f, 0.0f });
    transform->get().setScale(0.65f);
    renderer->get().setRenderType(RenderType::R_ANIMATE);
    renderer->get().setModel(
        &data->models[static_cast<typename std::underlying_type<bomberman::ModelType>::type>(
                          bomberman::ModelType::M_PLAYER_1)
                      + id]);
    renderer->get().addAnimation("assets/models/player.iqm");
    setKeyboard();
    setPosition();
    setPlayerType(PlayerType::NORMAL);
    addComponent(BoxCollider(transform->get().getPosition(), transform->get().getSize(), true));
}

int Player::findPrevType() const noexcept
{
    auto new_type = static_cast<typename std::underlying_type<PlayerType>::type>(type);
    if (new_type > 0) {
        new_type--;
    } else
        new_type =
            static_cast<typename std::underlying_type<PlayerType>::type>(PlayerType::__size__) - 1;
    return (new_type);
}

int Player::findNextType() const noexcept
{
    auto new_type = static_cast<typename std::underlying_type<PlayerType>::type>(type);
    if (new_type
        < (static_cast<typename std::underlying_type<PlayerType>::type>(PlayerType::__size__)
            - 1)) {
        new_type++;
    } else
        new_type = 0;
    return (new_type);
}

void Player::Update()
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    bool animate   = false;

    if (!hitbox.has_value() || !transform.has_value() || !renderer.has_value())
        throw(Error("Error in updating the player element.\n"));
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
    if (wallpass || wallpassEnd) {
        renderer->get().setColor(colors[colorIndex]);
        colorIndex = (colorIndex + 1) % colors.size();
    }
    if (controller.isGamepadConnected(id)) {
        // Mouvements au joystick
        float axisX = controller.getGamepadAxis(id, Axis::G_AXIS_LEFT_X);
        float axisY = controller.getGamepadAxis(id, Axis::G_AXIS_LEFT_Y);

        if (axisX != 0 || axisY != 0) animate = true;
        if (axisY < -0.5f && !isCollidingNextTurn(*bombs, 0, -1)) {
            transform->get().setRotationAngle(270.0f);
            transform->get().moveZ(-speed);
        }
        if (axisY > 0.5f && !isCollidingNextTurn(*bombs, 0, 1)) {
            transform->get().setRotationAngle(90.0f);
            transform->get().moveZ(speed);
        }
        if (axisX < -0.5f && !isCollidingNextTurn(*bombs, -1, 0)) {
            transform->get().setRotationAngle(0.0f);
            transform->get().moveX(-speed);
        }
        if (axisX > 0.5f && !isCollidingNextTurn(*bombs, 1, 0)) {
            transform->get().setRotationAngle(180.0f);
            transform->get().moveX(speed);
        }
        if (controller.isGamepadButtonPressed(id, G_Button::G_B)) placeBomb();
    } else {
        // Mouvements au clavier
        if (controller.isKeyDown(moveUp) || controller.isKeyDown(moveDown)
            || controller.isKeyDown(moveLeft) || controller.isKeyDown(moveRight))
            animate = true;
        if (controller.isKeyDown(moveUp) && !isCollidingNextTurn(*bombs, 0, -1)) {
            transform->get().setRotationAngle(270.0f);
            transform->get().moveZ(-speed);
        }
        if (controller.isKeyDown(moveDown) && !isCollidingNextTurn(*bombs, 0, 1)) {
            transform->get().setRotationAngle(90.0f);
            transform->get().moveZ(speed);
        }
        if (controller.isKeyDown(moveLeft) && !isCollidingNextTurn(*bombs, -1, 0)) {
            transform->get().setRotationAngle(0.0f);
            transform->get().moveX(-speed);
        }
        if (controller.isKeyDown(moveRight) && !isCollidingNextTurn(*bombs, 1, 0)) {
            transform->get().setRotationAngle(180.0f);
            transform->get().moveX(speed);
        }
        if (controller.isKeyPressed(dropBomb)) placeBomb();
    }
    if (!animate) {
        renderer->get().setSkipFrame(1);
        renderer->get().setAnimationId(1);
    } else {
        renderer->get().setSkipFrame(2);
        renderer->get().setAnimationId(0);
    }
}

PlayerType Player::getType() const noexcept
{
    return (type);
}

void Player::OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Wall>(other.get()) || Type:: instanceof <Fire>(other.get())) {
        if (other->getEnabledValue()) {
            killSound_.play();
            setEnabledValue(false);
        }
    }
}

void Player::setPosition()
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value()) throw(Error("Error in setting player position.\n"));

    transform->get().setRotationAngle(direction[id]);
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

void Player::setKeyboard() noexcept
{
    switch (id) {
        case 0:
            moveUp    = Key::K_W;
            moveDown  = Key::K_S;
            moveLeft  = Key::K_A;
            moveRight = Key::K_D;
            dropBomb  = Key::K_Q;
            break;
        case 1:
            moveUp    = Key::K_KP_8;
            moveDown  = Key::K_KP_5;
            moveLeft  = Key::K_KP_4;
            moveRight = Key::K_KP_6;
            dropBomb  = Key::K_KP_7;
            break;
        case 2:
            moveUp    = Key::K_T;
            moveDown  = Key::K_G;
            moveLeft  = Key::K_F;
            moveRight = Key::K_H;
            dropBomb  = Key::K_R;
            break;
        case 3:
            moveUp    = Key::K_I;
            moveDown  = Key::K_K;
            moveLeft  = Key::K_J;
            moveRight = Key::K_L;
            dropBomb  = Key::K_U;
            break;
        default: break;
    }
}

bool Player::isCollidingNextTurn(std::vector<std::unique_ptr<Entity>>& others, int xdir, int zdir)
{
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value() || !hitbox.has_value())
        throw(Error("Error in updating the collision of the player.\n"));

    Vector3D position = transform->get().getPosition();
    Vector3D nextTurn = { position.x + (speed * xdir * GetFrameTime()),
        position.y,
        position.z + (speed * zdir * GetFrameTime()) };

    if (!getEnabledValue()) return false;
    for (auto& other : others) {
        if (hitbox == std::nullopt || other->getComponent<BoxCollider>() == std::nullopt) continue;
        auto other_hitbox = other->getComponent<BoxCollider>();
        if (other_hitbox.has_value()) {
            if (!hitbox->get().getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
            if (other_hitbox->get().isColliding(hitbox->get(), nextTurn)) {
                if (Type:: instanceof <Bomb>(other.get())) return true;
                if (Type:: instanceof <Wall>(other.get())) return true;
                if (Type:: instanceof <Crate>(other.get())) {
                    if (wallpass) return false;
                    if (!wallpass && wallpassEnd) return false;
                    return true;
                }
            }
        }
    }
    if (wallpassEnd) {
        wallpassEnd = false;
        renderer->get().setColor(Colors::C_WHITE);
    }
    return false;
}

void Player::placeBomb()
{
    auto transform = getComponent<Transform3D>();
    if (!transform.has_value()) throw(Error("Error in updating the placement of bombs.\n"));
    for (auto& i : *bombs) {
        auto bomb = i->getComponent<Transform3D>();
        if (bomb.has_value()
            && bomb->get().getPosition().x == round(transform->get().getPosition().x)
            && bomb->get().getPosition().z == round(transform->get().getPosition().z))
            return;
    }
    if (nbBomb <= 0) return;
    nbBomb--;
    bombs->emplace_back(std::make_unique<Bomb>(transform->get().getPosition(),
        this,
        &data->models[static_cast<int>(bomberman::ModelType::M_BOMB)],
        bombSize,
        data,
        bombs));
}

void Player::setBombArray(std::vector<std::unique_ptr<Entity>>* bombsArray) noexcept
{
    bombs = bombsArray;
}

void Player::setWallPass(const bool& pass) noexcept
{
    this->wallpassTimer->resetTimer();
    wallpass = pass;
}

void Player::addItem(ItemType itemType) noexcept
{
    items.emplace_back(itemType);
}

void Player::dispatchItem(void) noexcept
{
    if (items.empty()) return;
    for (auto& item : items) { data->_entities->emplace_back(std::make_unique<Item>(data, item)); }
    items.clear();
}

void Player::setPlayerType(PlayerType type) noexcept
{
    this->type = type;
    switch (type) {
        case PlayerType::NORMAL:
            nbBomb      = 1;
            speed       = 2.0f;
            bombSize    = 3;
            nbBombMax   = 6;
            speedMax    = 3.5f;
            bombSizeMax = 6;
            break;
        case PlayerType::ATTACK:
            nbBomb      = 2;
            speed       = 1.7f;
            bombSize    = 4;
            nbBombMax   = 10;
            speedMax    = 2.5f;
            bombSizeMax = 10;
            break;
        case PlayerType::TACTICAL:
            nbBomb      = 2;
            speed       = 2.0f;
            bombSize    = 2;
            nbBombMax   = 5;
            speedMax    = 3.0f;
            bombSizeMax = 10;
            break;
        case PlayerType::RUNNER:
            nbBomb      = 1;
            speed       = 2.5f;
            bombSize    = 2;
            nbBombMax   = 3;
            speedMax    = 5.0f;
            bombSizeMax = 5;
            break;
        default: break;
    }
}

int Player::getNbBombMax() const noexcept
{
    return nbBombMax;
}

float Player::getSpeedMax() const noexcept
{
    return speedMax;
}

int Player::getBombSizeMax() const noexcept
{
    return bombSizeMax;
}

float Player::getSpeed() const noexcept
{
    return speed;
}

int Player::getNbBomb() const noexcept
{
    return nbBomb;
}

int Player::getBombSize() const noexcept
{
    return bombSize;
}

void Player::setSpeed(const float& speed) noexcept
{
    this->speed = speed;
}

void Player::setNbBomb(const int& nbBomb) noexcept
{
    this->nbBomb = nbBomb;
}

void Player::setBombSize(const int& bombSize) noexcept
{
    this->bombSize = bombSize;
}

PlayerType Player::getPlayerType() const noexcept
{
    return type;
}
