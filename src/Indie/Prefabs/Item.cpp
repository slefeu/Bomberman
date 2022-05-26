/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Item
*/

#include "Item.hpp"

#include <iostream>

#include "Player.hpp"

Item::Item(Vector3 pos, GameData* data) noexcept
{
    transform3d.setPosition(pos);
    transform3d.setScale(1.0f);
    transform3d.setRotationAxis({ 1.0f, 0.0f, 0.0f });
    transform3d.setRotationAngle(90.0f);
    render.setRenderType(RenderType::R_3DMODEL_ROTATE);

    Vector3 vectortemp = { 1.0f, 1.0f, 0.5f };
    type               = EntityType::E_ITEM;
    hitbox             = NEW_HITBOX(transform3d.getPosition(), vectortemp, true);
    hitbox->isSolid    = false;

    transform3d.addZ((transform3d.getScale() / 2) * -1);
    transform3d.addY((transform3d.getScale() / 2));
    hitbox->position.z += transform3d.getScale() / 10;
    hitbox->position.y += transform3d.getScale() / 2;
    hitbox->update(hitbox->position);

    itemType = (ItemType)((int)rand() % 3);
    switch (itemType) {
        case ItemType::I_SPEEDUP: render.setModel(MODELS(M_IROLLER)); break;
        case ItemType::I_BOMBUP: render.setModel(MODELS(M_IBOMB)); break;
        case ItemType::I_FIREUP: render.setModel(MODELS(M_IFIRE)); break;
        default: break;
    }
}

void Item::Display() noexcept
{
    render.display(transform3d);
    hitbox->display();
}

void Item::Update() noexcept {}

void Item::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_PLAYER) {
        setPlayerStat((std::unique_ptr<Player>&)other);
        isEnable = false;
    }
}

void Item::setPlayerStat(std::unique_ptr<Player>& p) noexcept
{
    switch (itemType) {
        case ItemType::I_SPEEDUP: p->speed += 0.2f; break;
        case ItemType::I_BOMBUP: p->nbBomb += 1; break;
        case ItemType::I_FIREUP: p->bombSize += 1; break;
        default: break;
    }
}