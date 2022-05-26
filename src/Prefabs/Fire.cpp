/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** Fire.cpp
** File description:
** Fire
*/

#include "Fire.hpp"

#include "Crate.hpp"
#include "GameObject3D.hpp"

Fire::Fire(Vector3 posi, float newSize) noexcept
{
    transform3d.setPosition(posi);
    transform3d.setSize({ newSize, newSize, newSize });

    type     = EntityType::E_FIRE;
    lifeTime = 0.5f;
    timer    = std::make_unique<Timer>(lifeTime);
    hitbox   = std::make_unique<BoxCollider>(transform3d.getPosition(), transform3d.getSize(), true);
}

bool Fire::update(void) noexcept
{
    display();
    timer->updateTimer();
    return timer->timerDone();
}

bool Fire::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    bool isColliding = false;

    for (auto& other : others) {
        if (other->hitbox == nullptr || hitbox == nullptr) continue;
        // if (!other->hitbox->isSolid || !hitbox->isSolid) continue;
        if (!isEnable || !other->isEnable) continue;
        if (hitbox->isColliding(other->hitbox)) {
            CollideAction(other);
            isColliding = true;
        }
    }
    return isColliding;
}

void Fire::CollideAction(std::unique_ptr<GameObject3D>& other) noexcept
{
    if (other->type == EntityType::E_PLAYER) other->isEnable = false;
    if (other->type == EntityType::E_CRATE) {
        ((std::unique_ptr<Crate>&)other)->dropItem();

        other->isEnable = false;
        other->hitbox.reset();
        other->hitbox = nullptr;
        isEnable      = false;
    }
    if (other->type == EntityType::E_ITEM) other->isEnable = false;
    if (other->type == EntityType::E_BOMB) other->setLifeTime(0.0);
}

void Fire::display() noexcept
{
    if (!isEnable) return;

    DrawCubeV(transform3d.getPosition(), transform3d.getSize(), RED);
    hitbox->display();
    hitbox->update(transform3d.getPosition());
}

void Fire::setLifeTime(float const& newLifeTime) noexcept
{
    lifeTime = newLifeTime;
}

// -------------------------- USELESS FUNCTIONS --------------------------

bool Fire::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return false;
}

void Fire::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    (void)others;
    return;
}

bool Fire::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
{
    (void)others;
    (void)xdir;
    (void)zdir;
    return false;
}
