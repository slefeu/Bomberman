/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

#include <iostream>
#include <memory>

#include "BoxCollider.hpp"
#include "Error.hpp"
#include "Player.hpp"
#include "Render.hpp"
#include "Transform3D.hpp"

Item::Item(Vector3 pos, GameData* data)
    : Entity(EntityType::E_ITEM)
    , getItemSound(GET_ITEM)
    , newItemSound(NEW_ITEM)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the item element.\n"));

    this->data = data;
    transform->get().setPosition(pos);
    transform->get().setScale(1.0f);
    transform->get().setRotationAxis({ 1.0f, 0.0f, 0.0f });
    transform->get().setRotationAngle(90.0f);
    renderer->get().setRenderType(RenderType::R_3DMODEL_ROTATE);

    addComponent(BoxCollider(transform->get().getPosition(), { 1.0f, 1.0f, 0.5f }, true));
    auto hitbox = getComponent<BoxCollider>();

    if (!hitbox.has_value()) throw(Error("Error, could not instanciate the item element.\n"));
    hitbox->get().setIsSolid(false);
    transform->get().addZ((transform->get().getScale() / 2) * -1);
    transform->get().addY((transform->get().getScale() / 2));

    hitbox->get().addZ(transform->get().getScale() / 10);
    hitbox->get().addY(transform->get().getScale() / 10);
    hitbox->get().update(hitbox->get().getPosition());

    itemType = (ItemType)(static_cast<int>(rand() % 4));
    setModelByType();

    newItemSound.play();
}

Item::Item(GameData* data, ItemType type)
    : Entity(EntityType::E_ITEM)
    , getItemSound(GET_ITEM)
    , newItemSound(NEW_ITEM)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the item element.\n"));

    this->data = data;
    transform->get().setPosition(findFreePosition());
    transform->get().setScale(1.0f);
    transform->get().setRotationAxis({ 1.0f, 0.0f, 0.0f });
    transform->get().setRotationAngle(90.0f);
    renderer->get().setRenderType(RenderType::R_3DMODEL_ROTATE);

    Vector3 scale = { 1.0f, 1.0f, 0.5f };
    addComponent(BoxCollider(transform->get().getPosition(), scale, true));
    auto hitbox = getComponent<BoxCollider>();

    if (!hitbox.has_value()) throw(Error("Error, could not instanciate the item element.\n"));
    hitbox->get().setIsSolid(false);
    transform->get().addZ((transform->get().getScale() / 2) * -1);
    transform->get().addY((transform->get().getScale() / 2));

    hitbox->get().addZ(transform->get().getScale() / 10);
    hitbox->get().addY(transform->get().getScale() / 10);
    hitbox->get().update(hitbox->get().getPosition());

    itemType = type;
    setModelByType();

    newItemSound.play();
}

void Item::Display()
{
    auto renderer  = getComponent<Render>();
    auto transform = getComponent<Transform3D>();

    if (!renderer.has_value() || !transform.has_value())
        throw(Error("Error in displaying an item element.\n"));
    renderer->get().display(transform->get());
}

void Item::Update() {}

void Item::OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_PLAYER) {
        setPlayerStat((std::unique_ptr<Player>&)other);
        ((std::unique_ptr<Player>&)other)->addItem(itemType);
        getItemSound.play();
        setEnabledValue(false);
    }
}

void Item::setPlayerStat(std::unique_ptr<Player>& p) noexcept
{
    switch (itemType) {
        case ItemType::I_SPEEDUP:
            if (p->getSpeed() < p->getSpeedMax()) p->setSpeed(p->getSpeed() + 0.2f);
            break;
        case ItemType::I_BOMBUP:
            if (p->getNbBomb() < p->getNbBombMax()) p->setNbBomb(p->getNbBomb() + 1);
            break;
        case ItemType::I_FIREUP:
            if (p->getBombSize() < p->getBombSizeMax()) p->setBombSize(p->getBombSize() + 1);
            break;
        case ItemType::I_WALL: p->setWallPass(true); break;
        default: break;
    }
}

Vector3 Item::findFreePosition(void) const noexcept
{
    Vector3 pos;
    int     x;
    int     z;

    do {
        x   = rand() % 12 - 6;
        z   = rand() % 12 - 5;
        pos = { x * 1.0f, 0.25f, z * 1.0f };
        std::cout << "INFO: Item from Player drop at x:" << pos.x << " z:" << pos.z << std::endl;
    } while (entitiesHere(pos));

    return pos;
}

bool Item::entitiesHere(Vector3& pos) const noexcept
{
    for (auto& entity : *data->_entities) {
        auto              transform    = entity->getComponent<Transform3D>();
        auto              other_hitbox = entity->getComponent<BoxCollider>();
        const BoxCollider hitbox =
            BoxCollider(transform->get().getPosition(), transform->get().getSize(), true);
        if (!other_hitbox || !other_hitbox.has_value()) continue;
        if (!hitbox.getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
        if (other_hitbox->get().isColliding(hitbox, pos)) return true;
    }
    return false;
}

void Item::displayModel(const Vector3& position) {}

void Item::setModelByType(void) noexcept
{
    auto renderer = getComponent<Render>();

    switch (itemType) {
        case ItemType::I_SPEEDUP:
            renderer->get().setModel(&data->models[static_cast<int>(ModelType::M_IROLLER)]);
            break;
        case ItemType::I_BOMBUP:
            renderer->get().setModel(&data->models[static_cast<int>(ModelType::M_IBOMB)]);
            break;
        case ItemType::I_FIREUP:
            renderer->get().setModel(&data->models[static_cast<int>(ModelType::M_IFIRE)]);
            break;
        case ItemType::I_WALL:
            renderer->get().setModel(&data->models[static_cast<int>(ModelType::M_IWALL)]);
            break;
        default: break;
    }
}
