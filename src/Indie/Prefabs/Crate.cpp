/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

#include "Error.hpp"
#include "Item.hpp"

Crate::Crate(Vector3                        pos,
    std::unique_ptr<Model3D>*               newModel,
    GameData*                               data,
    std::vector<std::unique_ptr<Entities>>* entities)
    : Entities(EntityType::E_CRATE)
    , data(data)
    , entities(entities)
{
    setEnabledValue(true);
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the crate element.\n"));
    transform->get().setPosition(pos);
    transform->get().setScale(0.015f);
    transform->get().setY(0 - transform->get().getScale());
    renderer->get().setRenderType(RenderType::R_3DMODEL);
    renderer->get().setModel(newModel);

    Vector3 position = {
        transform->get().getPositionX(), 0.35f, transform->get().getPositionZ()
    };
    Vector3 size = { 0.8f, 0.8f, 0.8f };
    addComponent(BoxCollider(position, size, true));
}

void Crate::Display()
{
    auto renderer  = getComponent<Render>();
    auto transform = getComponent<Transform3D>();

    if (!renderer.has_value() || !transform.has_value())
        throw(Error("Error in displaying a crate element.\n"));
    if (!getEnabledValue()) return;
    renderer->get().display(transform->get());
}

void Crate::Update()
{
    if (!getEnabledValue()) return;
}

void Crate::dropItem()
{
    auto transform = getComponent<Transform3D>();

    if (!transform.has_value()) throw(Error("Error in dropping item.\n"));
    if (rand() % 3 != 0) return;
    entities->emplace_back(NEW_ITEM(transform->get().getPosition(), data));
}

void Crate::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_WALL) setEnabledValue(false);
}