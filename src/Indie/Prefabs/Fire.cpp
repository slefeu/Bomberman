/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** Fire.cpp
** File description:
** Fire
*/

#include "Fire.hpp"

#include <iostream>

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Entities.hpp"
#include "Error.hpp"

Fire::Fire(Vector3 posi, std::unique_ptr<Model3D>* model)
    : Entities(EntityType::E_FIRE)
    , explodeTime(0.5f)
    , explodeTimer(NEW_TIMER(explodeTime))
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the player element.\n"));
    transform->get().setPosition({ posi.x - 5.6f, posi.y - 0.5f, posi.z - 3.5f });
    transform->get().setScale(2.0f);

    std::cout << "posi : " << posi.x << " " << posi.y << " " << posi.z << std::endl;
    // transform->get().setRotationAxis({ 0.0f, 0.0f, 0.0f });
    // transform->get().setRotationAngle(0.0f);
    transform->get().setSize({ 0.5f, 0.5f, 0.5f });
    renderer->get().setRenderType(RenderType::R_3DMODEL);
    renderer->get().setModel(model);
    addComponent(BoxCollider({ posi.x, posi.y, posi.z }, transform->get().getSize(), true));
}

void Fire::Display()
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();
    auto hitbox    = getComponent<BoxCollider>();

    if (!transform.has_value() || !renderer.has_value() || !hitbox.has_value())
        throw(Error("Error in displaying the player element.\n"));
    renderer->get().display(transform->get());
    hitbox->get().display();
}

void Fire::Update()
{
    explodeTimer->updateTimer();
    if (explodeTimer->timerDone()) setEnabledValue(false);
}

void Fire::OnCollisionEnter(std::unique_ptr<Entities>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_PLAYER) other->setEnabledValue(false);
}

bool Fire::ExplodeElements(std::unique_ptr<Entities>& other) noexcept
{
    if (other->getEntityType() == EntityType::E_CRATE) {
        ((std::unique_ptr<Crate>&)other)->dropItem();
        other->setEnabledValue(false);
        return true;
    }
    if (other->getEntityType() == EntityType::E_ITEM) {
        other->setEnabledValue(false);
        return false;
    }
    if (other->getEntityType() == EntityType::E_WALL) return true;
    if (other->getEntityType() == EntityType::E_BOMB) {
        ((std::unique_ptr<Bomb>&)other)->explode();
        return true;
    }
    return false;
}