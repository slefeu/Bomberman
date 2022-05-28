/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#include "Box.hpp"

#include "Error.hpp"

Box::Box(Vector3 pos, Vector3 newSize)
    : Entities(EntityType::E_BOX)
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the box element.\n"));

    transform->get().setPosition(pos);
    transform->get().setSize(newSize);
    renderer->get().setRenderType(RenderType::R_CUBE);
    renderer->get().setColor(BLUE);

    addComponent(BoxCollider(
        transform->get().getPosition(), transform->get().getSize(), true));
}

void Box::Display()
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error in updating the game.\n"));
    renderer->get().display(transform->get());
}

void Box::Update()
{
    auto transform = getComponent<Transform3D>();
    auto hitbox    = getComponent<BoxCollider>();
    if (!transform.has_value() || !hitbox.has_value())
        throw(Error("Error in updating the game.\n"));
    hitbox->get().update(transform->get().getPosition());
}