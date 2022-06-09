/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** Fire.cpp
** File description:
** Fire
*/

#include "Fire.hpp"

#include "Bomb.hpp"
#include "Crate.hpp"
#include "Entity.hpp"
#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Item.hpp"
#include "Wall.hpp"

Fire::Fire(Vector3D posi, std::unique_ptr<Model3D>* model)
    : Entity()
    , explodeTime(0.5f)
    , explodeTimer(std::make_unique<Timer>(explodeTime))
{
    addComponent(Transform3D());
    addComponent(Render());
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the player element.\n"));

    transform->get().setPosition({ posi.x, posi.y - 0.3f, posi.z });
    transform->get().setScale(1.2f);
    transform->get().setSize({ 0.5f, 0.5f, 0.5f });
    transform->get().setRotationAxis({ 1.0f, 0.0f, 0.0f });
    transform->get().setRotationAngle(-90.0f);
    renderer->get().setRenderType(RenderType::R_ANIMATE);
    renderer->get().setModel(model);
    renderer->get().addAnimation("assets/models/fire.iqm");

    addComponent(BoxCollider({ posi.x, posi.y, posi.z }, transform->get().getSize(), true));
}

void Fire::Display()
{
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error in displaying the player element.\n"));
    renderer->get().display(transform->get());
}

void Fire::Update()
{
    explodeTimer->updateTimer();
    if (explodeTimer->timerDone()) setEnabledValue(false);
}

void Fire::OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Player>(other.get())) {
        ((std::unique_ptr<Player>&)other)->dispatchItem();
        other->setEnabledValue(false);
    }
}

bool Fire::ExplodeElements(std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Crate>(other.get())) {
        ((std::unique_ptr<Crate>&)other)->dropItem();
        other->setEnabledValue(false);
        return true;
    }
    if (Type:: instanceof <Item>(other.get())) {
        other->setEnabledValue(false);
        return false;
    }
    if (Type:: instanceof <Wall>(other.get())) return true;
    if (Type:: instanceof <Bomb>(other.get())) {
        ((std::unique_ptr<Bomb>&)other)->explode();
        return true;
    }
    return false;
}
