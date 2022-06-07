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
    : Entities(EntityType::E_ITEM)
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

    itemType = (ItemType)(static_cast<int>(rand() % 4));
    switch (itemType) {
        case ItemType::I_SPEEDUP: renderer->get().setModel(MODELS(M_IROLLER)); break;
        case ItemType::I_BOMBUP: renderer->get().setModel(MODELS(M_IBOMB)); break;
        case ItemType::I_FIREUP: renderer->get().setModel(MODELS(M_IFIRE)); break;
        case ItemType::I_WALL: renderer->get().setModel(MODELS(M_IWALL)); break;
        default: break;
    }
}

Item::Item(GameData* data, ItemType type)
    : Entities(EntityType::E_ITEM)
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

    switch (itemType) {
        case ItemType::I_SPEEDUP: renderer->get().setModel(MODELS(M_IROLLER)); break;
        case ItemType::I_BOMBUP: renderer->get().setModel(MODELS(M_IBOMB)); break;
        case ItemType::I_FIREUP: renderer->get().setModel(MODELS(M_IFIRE)); break;
        case ItemType::I_WALL: renderer->get().setModel(MODELS(M_IWALL)); break;
        default: break;
    }
}

void Item::Display()
{
    auto renderer  = getComponent<Render>();
    auto transform = getComponent<Transform3D>();
    auto hitbox    = getComponent<BoxCollider>();

    if (!renderer.has_value() || !transform.has_value() || !hitbox.has_value())
        throw(Error("Error in displaying an item element.\n"));
    renderer->get().display(transform->get());
    hitbox->get().display();
}

void Item::Update() {}

void Item::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_PLAYER) {
        setPlayerStat((std::unique_ptr<Player>&)other);
        ((std::unique_ptr<Player>&)other)->addItem(itemType);
        setEnabledValue(false);
    }
}

void Item::setPlayerStat(std::unique_ptr<Player>& p) noexcept
{
    switch (itemType) {
        case ItemType::I_SPEEDUP: p->speed += 0.2f; break;
        case ItemType::I_BOMBUP: p->nbBomb += 1; break;
        case ItemType::I_FIREUP: p->bombSize += 1; break;
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
        z   = rand() % 12 - 6;
        pos = { x * 1.0f, 0.25f, z * 1.0f };
        std::cout << "Item from Player drop at x:" << pos.x << " z:" << pos.z << std::endl;
    } while (entitiesHere(pos));

    return pos;
}

bool Item::entitiesHere(Vector3& pos) const noexcept
{
    for (auto& entity : *data->_entities) {
        auto              transform    = entity->getComponent<Transform3D>();
        auto              other_hitbox = entity->getComponent<BoxCollider>();
        const BoxCollider hitbox       = BoxCollider(transform->get().getPosition(), transform->get().getSize(), true);
        if (!other_hitbox || !other_hitbox.has_value()) continue;
        if (!hitbox.getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
        if (other_hitbox->get().isColliding(hitbox, pos)) return true;
    }
    return false;
}
