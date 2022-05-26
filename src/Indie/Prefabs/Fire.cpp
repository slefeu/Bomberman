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
#include "GameObject3D.hpp"

Fire::Fire(Vector3 posi, float newSize) noexcept
    : explodeTime(0.5f)
    , explodeTimer(NEW_TIMER(explodeTime))
{
    transform3d.setPosition(posi);
    transform3d.setSize({ newSize, newSize, newSize });
    render.setRenderType(RenderType::R_CUBE);
    render.setColor(RED);

    type   = EntityType::E_FIRE;
    hitbox = NEW_HITBOX(transform3d.getPosition(), transform3d.getSize(), true);
}

void Fire::Display() noexcept
{
    render.display(transform3d);
    hitbox->display();
}

void Fire::Update() noexcept
{
    explodeTimer->updateTimer();
    if (explodeTimer->timerDone()) isEnable = false;
}

void Fire::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_PLAYER) other->isEnable = false;
}

bool Fire::ExplodeElements(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_CRATE) {
        ((std::unique_ptr<Crate>&)other)->dropItem();
        other->isEnable = false;
        isEnable        = false;
        return true;
    }
    if (other->type == EntityType::E_ITEM) {
        other->isEnable = false;
        return false;
    }
    if (other->type == EntityType::E_WALL) return true;
    if (other->type == EntityType::E_BOMB) {
        ((std::unique_ptr<Bomb>&)other)->explode();
        return true;
    }
    return false;
}