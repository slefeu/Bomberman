/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

#include <memory>

#include "Bomberman.hpp"
#include "BoxCollider.hpp"
#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Player.hpp"
#include "Render.hpp"
#include "Transform3D.hpp"

Item::Item(Vector3D pos, GameData& data)
    : Entity()
    , data(data)
    , itemType(static_cast<bomberman::ItemType>(static_cast<int>(rand() % 4)))
    , getItemSound(GET_ITEM)
    , newItemSound(NEW_ITEM)
{
    addComponent(Transform3D());
    addComponent(Render(findItemModel()));
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

    newItemSound.play();
}

Item::Item(GameData& data, bomberman::ItemType type)
    : Entity()
    , data(data)
    , itemType(type)
    , getItemSound(GET_ITEM)
    , newItemSound(NEW_ITEM)

{
    addComponent(Transform3D());
    addComponent(Render(findItemModel()));
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the item element.\n"));

    transform->get().setPosition(findFreePosition());
    transform->get().setScale(1.0f);
    transform->get().setRotationAxis({ 1.0f, 0.0f, 0.0f });
    transform->get().setRotationAngle(90.0f);
    renderer->get().setRenderType(RenderType::R_3DMODEL_ROTATE);

    Vector3D scale = { 1.0f, 1.0f, 0.5f };
    addComponent(BoxCollider(transform->get().getPosition(), scale, true));
    auto hitbox = getComponent<BoxCollider>();

    if (!hitbox.has_value()) throw(Error("Error, could not instanciate the item element.\n"));
    hitbox->get().setIsSolid(false);
    transform->get().addZ((transform->get().getScale() / 2) * -1);
    transform->get().addY((transform->get().getScale() / 2));

    hitbox->get().addZ(transform->get().getScale() / 10);
    hitbox->get().addY(transform->get().getScale() / 10);
    hitbox->get().update(hitbox->get().getPosition());
    newItemSound.play();
}

Model3D& Item::findItemModel() const noexcept
{
    const auto& model = data.getModels();

    switch (itemType) {
        case bomberman::ItemType::I_SPEEDUP:
            return (*model.at(static_cast<int>(bomberman::ModelType::M_IROLLER)));
        case bomberman::ItemType::I_BOMBUP:
            return (*model.at(static_cast<int>(bomberman::ModelType::M_IBOMB)));
        case bomberman::ItemType::I_FIREUP:
            return (*model.at(static_cast<int>(bomberman::ModelType::M_IFIRE)));
        case bomberman::ItemType::I_WALL:
        default: return (*model.at(static_cast<int>(bomberman::ModelType::M_IWALL)));
    }
}

void Item::Update() {}

void Item::OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Player>(other.get())) {
        setPlayerStat((std::unique_ptr<Player>&)other);
        ((std::unique_ptr<Player>&)other)->addItem(itemType);
        getItemSound.play();
        setEnabledValue(false);
    }
}

void Item::setPlayerStat(std::unique_ptr<Player>& p) noexcept
{
    switch (itemType) {
        case bomberman::ItemType::I_SPEEDUP:
            if (p->getSpeed() < p->getSpeedMax()) p->setSpeed(p->getSpeed() + 0.2f);
            break;
        case bomberman::ItemType::I_BOMBUP:
            if (p->getNbBomb() < p->getNbBombMax()) p->setNbBomb(p->getNbBomb() + 1);
            break;
        case bomberman::ItemType::I_FIREUP:
            if (p->getBombSize() < p->getBombSizeMax()) p->setBombSize(p->getBombSize() + 1);
            break;
        case bomberman::ItemType::I_WALL: p->setWallPass(true); break;
        default: break;
    }
}

Vector3D Item::findFreePosition(void) const noexcept
{
    Vector3D pos;
    int      x;
    int      z;

    do {
        x   = rand() % 12 - 6;
        z   = rand() % 12 - 5;
        pos = { x * 1.0f, 0.25f, z * 1.0f };
    } while (entitiesHere(pos));

    return (pos);
}

bool Item::entitiesHere(Vector3D& pos) const noexcept
{
    for (auto& entity : data.getEntities()) {
        auto transform    = entity->getComponent<Transform3D>();
        auto other_hitbox = entity->getComponent<BoxCollider>();
        if (!transform.has_value()) continue;
        auto posTemp = transform->get().getPosition();

        const BoxCollider hitbox =
            BoxCollider({ posTemp.x, posTemp.y, posTemp.z }, { 0.5f, 0.5f, 0.5f }, true);
        if (!other_hitbox || !other_hitbox.has_value()) continue;
        if (!hitbox.getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
        if (other_hitbox->get().isColliding(hitbox, pos)) return true;
    }
    return false;
}