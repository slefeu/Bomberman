/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Bomb
*/

#include "Bomb.hpp"

#include "Error.hpp"
#include "InstanceOf.hpp"
#include "Wall.hpp"

Bomb::Bomb(Vector3D                       pos,
    Player*                               p,
    std::unique_ptr<Model3D>*             newModel,
    int                                   bombSize,
    GameData*                             data,
    std::vector<std::unique_ptr<Entity>>* entities)
    : Entity()
    , lifeTime(3.0f)
    , lifeTimer(std::make_unique<Timer>(lifeTime))
    , player(p)
    , size(bombSize)
    , hasHitbox(false)
    , data(data)
    , entities(entities)
    , is_exploding_(false)
    , animeDir(1)
    , dropSound_(DROP_BOMB)
    , explodeSound(EXPLODE)
{
    addComponent(Transform3D());
    addComponent(Render());
    auto transform = getComponent<Transform3D>();
    auto renderer  = getComponent<Render>();

    if (!transform.has_value() || !renderer.has_value())
        throw(Error("Error, could not instanciate the bomb element.\n"));

    transform->get().setScale(0.07f);
    transform->get().setPosition(
        { round(pos.x), 0.0f - transform->get().getScale(), round(pos.z) });
    renderer->get().setRenderType(RenderType::R_3DMODEL);
    renderer->get().setModel(newModel);

    addComponent(BoxCollider(transform->get().getPosition(), { 0.8f, 1.2f, 0.8f }, false));

    explodeSound.setVolume(1.0f);
    dropSound_.play();
}

void Bomb::Update()
{
    int  i         = 0;
    auto hitbox    = getComponent<BoxCollider>();
    auto transform = getComponent<Transform3D>();
    if (!hitbox.has_value() || !transform.has_value())
        throw(Error("Error in updating a bomb element.\n"));

    lifeTimer->updateTimer();
    if (lifeTimer->timerDone()) {
        explode();
        return;
    }
    if (fires.size() == 0 && !hitbox->get().getIsSolid()) {
        if (data->players.size() <= 0) return;

        for (auto& other : data->players) {
            if (!(other->getComponent<BoxCollider>().has_value())) continue;
            auto other_collider = other->getComponent<BoxCollider>();
            if (!hitbox->get().isColliding(other_collider->get())) i++;
        }
        if (i == static_cast<int>(data->players.size())) hitbox->get().setIsSolid(true);
    }

    transform->get().setScale(transform->get().getScale() + (0.1f * GetFrameTime() * animeDir));
    if (transform->get().getScale() > 0.09f || transform->get().getScale() < 0.07f) animeDir *= -1;
}

void Bomb::explode() noexcept
{
    auto hitbox = getComponent<BoxCollider>();

    explodeSound.play();

    if (is_exploding_) return;
    is_exploding_ = true;
    hitbox->get().setIsSolid(false);
    if (player->getNbBombMax() > player->getNbBomb()) player->setNbBomb(player->getNbBomb() + 1);
    fires.emplace_back(std::make_unique<Fire>(getComponent<Transform3D>()->get().getPosition(),
        &data->models[static_cast<int>(bomberman::ModelType::M_FIRE)]));
    createFire({ 1.0f, 0.0f, 0.0f });
    createFire({ -1.0f, 0.0f, 0.0f });
    createFire({ 0.0f, 0.0f, 1.0f });
    createFire({ 0.0f, 0.0f, -1.0f });

    for (auto& fire : fires) { entities->emplace_back(std::move(fire)); }
    setEnabledValue(false);
}

void Bomb::createFire(Vector3D mul) noexcept
{
    Vector3D position = getComponent<Transform3D>()->get().getPosition();
    Vector3D newPos;
    bool     exit = false;

    for (int i = 1; i < size && !exit; i++) {
        newPos.x = position.x + (float(i) * mul.x);
        newPos.y = position.y + (float(i) * mul.y);
        newPos.z = position.z + (float(i) * mul.z);
        fires.emplace_back(std::make_unique<Fire>(
            newPos, &data->models[static_cast<int>(bomberman::ModelType::M_FIRE)]));
        auto& fire = fires.back();
        for (auto& other : *entities) {
            auto collider      = fire->getComponent<BoxCollider>();
            auto other_collide = other->getComponent<BoxCollider>();
            if (collider->get().isColliding(other_collide->get()))
                if ((exit = fire->ExplodeElements(other))) break;
        }
    }
}

void Bomb::OnCollisionEnter([[maybe_unused]] std::unique_ptr<Entity>& other) noexcept
{
    if (Type:: instanceof <Wall>(other.get())) explode();
}
