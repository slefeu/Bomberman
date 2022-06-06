/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

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

    newItemSound.play();
}

Item::~Item() noexcept
{
    getItemSound.unload();
    newItemSound.unload();
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
