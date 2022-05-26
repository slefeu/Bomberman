

/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Explosion
*/

#include "Explosion.hpp"

#include <iostream>

#include "Collision.hpp"

Explosion::Explosion(Vector3 posi, int newSize, std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
{
    transform3d.setPosition(posi);
    transform3d.setSize({ 10.0f, 0.2f, 0.2f });

    (void)others;

    type          = EntityType::E_EXPLOSION;
    hitbox        = nullptr;
    lifeTime      = 0.5f;
    explosionSize = newSize;
    timer         = std::make_unique<Timer>(lifeTime);
    fires.emplace_back(std::make_unique<Fire>(transform3d.getPosition(), 0.9f));
    // extandExplosion(others);
}

void Explosion::Display() noexcept
{
    for (auto& fire : fires) { fire->Display(); }
}

void Explosion::Update() noexcept
{
    hitbox->update(transform3d.getPosition());
}

void Explosion::OnCollisionEnter(std::unique_ptr<GameObject3D>& other) noexcept
{
    (void)other;
}

// void Explosion::display() noexcept
// {
//     for (auto& fire : fires) { fire->display(); }
// }

// void Explosion::extandExplosion(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     Vector3 position = transform3d.getPosition();
//     float   size     = 0.5f;

//     for (int i = 1; i < explosionSize; i++) {
//         Vector3 newPos = { position.x + float(i), position.y, position.z };
//         fires.emplace_back(std::make_unique<Fire>(newPos, size));
//         if (fires.back()->isColliding(others)) break;
//     }
//     for (int i = 1; i < explosionSize; i++) {
//         Vector3 newPos = { position.x - float(i), position.y, position.z };
//         fires.emplace_back(std::make_unique<Fire>(newPos, size));
//         if (fires.back()->isColliding(others)) break;
//     }
//     for (int i = 1; i < explosionSize; i++) {
//         Vector3 newPos = { position.x, position.y, position.z + float(i) };
//         fires.emplace_back(std::make_unique<Fire>(newPos, size));
//         if (fires.back()->isColliding(others)) break;
//     }
//     for (int i = 1; i < explosionSize; i++) {
//         Vector3 newPos = { position.x, position.y, position.z - float(i) };
//         fires.emplace_back(std::make_unique<Fire>(newPos, size));
//         if (fires.back()->isColliding(others)) break;
//     }
// }

// bool Explosion::isColliding(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     bool explosionColliding = false;

//     for (auto& fire : fires) {
//         if (fire->isColliding(others)) explosionColliding = true;
//     }
//     return explosionColliding;
// }

// bool Explosion::update(void) noexcept
// {
//     display();
//     for (auto& fire : fires) { fire->update(); }
//     timer->updateTimer();
//     return timer->timerDone();
// }

// // -------------------------- USELESS FUNCTIONS --------------------------

// void Explosion::setLifeTime(float const& newLifeTime) noexcept
// {
//     (void)newLifeTime;
// }

// void Explosion::action(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     (void)others;
//     return;
// }

// bool Explosion::isCollidingNextTurn(std::vector<std::unique_ptr<GameObject3D>>& others, int xdir, int zdir) noexcept
// {
//     (void)others;
//     (void)xdir;
//     (void)zdir;
//     return false;
// }

// bool Explosion::update(std::vector<std::unique_ptr<GameObject3D>>& others) noexcept
// {
//     (void)others;
//     return false;
// }

// void Explosion::CollideAction(std::unique_ptr<GameObject3D>& other) noexcept
// {
//     (void)other;
// }
