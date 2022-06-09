/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#include "Crate.hpp"

#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Item.hpp"
#include "Wall.hpp"

Crate::Crate(Vector3D                     pos,
    std::unique_ptr<Model3D>*             newModel,
    GameData*                             data,
    std::vector<std::unique_ptr<Entity>>* entities)
    : Entity()
    , data(data)
    , entities(entities)
{
    addComponent(Transform3D());
    addComponent(Render());
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

    addComponent(
        BoxCollider({ transform->get().getPositionX(), 0.35f, transform->get().getPositionZ() },
            { 0.8f, 0.8f, 0.8f },
            true));
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
    entities->emplace_back(std::make_unique<Item>((Vector3D)transform->get().getPosition(), data));
}

void Crate::OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Wall>(other.get())) setEnabledValue(false);
}
