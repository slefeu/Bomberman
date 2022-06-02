/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Wall
*/

#include "Wall.hpp"

#include <iostream>

#include "Error.hpp"

Wall::Wall(Vector3 pos, std::unique_ptr<Model3D>* model)
    : Entities(EntityType::E_WALL)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the bomb element.\n"));
    transform->get().setPosition(pos);
    transform->get().setScale(0.017f);
    renderer->get().setRenderType(RenderType::R_3DMODEL);
    renderer->get().setModel(model);
    Vector3 size = { 1.0f, 1.0f, 1.0f };
    addComponent(BoxCollider(transform->get().getPosition(), size, true));
}

void Wall::Display()
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value()) throw(Error("Error in updating the game.\n"));
    renderer->get().display(transform->get());
}

void Wall::Update()
{
    if (!getEnabledValue()) return;
    auto transform = getComponent<Transform3D>();

    if (transform->get().getPosition().y > 0) { transform->get().moveY(-4.0f); }
    if (transform->get().getPosition().y < 0) { transform->get().setY(0.0f); }

    getComponent<BoxCollider>()->get().update(transform->get().getPosition());
}

void Wall::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    (void)other;
}
