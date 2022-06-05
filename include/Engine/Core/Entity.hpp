/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Entity
*/

#pragma once

#include <functional>
#include <memory>
#include <optional>
#include <type_traits>
#include <vector>

#include "BoxCollider.hpp"
#include "Controller.hpp"
#include "Model3D.hpp"
#include "Render.hpp"
#include "Transform3D.hpp"

enum class EntityType { E_PLAYER, E_BOX, E_BOMB, E_CRATE, E_WALL, E_FIRE, E_ITEM };

class Entity
{
  public:
    Entity(const EntityType& type) noexcept;
    virtual ~Entity() noexcept           = default;
    Entity(const Entity& other) noexcept = delete;
    Entity(Entity&& other) noexcept      = delete;
    Entity& operator=(const Entity& rhs) noexcept = delete;
    Entity& operator=(Entity&& rhs) noexcept = delete;

    virtual void Display()                                                 = 0;
    virtual void displayModel(const Vector3& position)                     = 0;
    virtual void Update()                                                  = 0;
    virtual void OnCollisionEnter(std::unique_ptr<Entity>& other) noexcept = 0;
    template <typename T>
    void addComponent(const T& component) noexcept
    {
        auto component_ptr = std::make_unique<T>(component);
        components_.push_back(std::move(component_ptr));
    };
    std::vector<std::unique_ptr<Component>>& getComponents() noexcept;
    template <typename T>
    std::optional<std::reference_wrapper<T>> getComponent() noexcept
    {
        for (auto& i : components_) {
            if (T::TYPE == i->getComponentType()) {
                auto value = dynamic_cast<T*>(i.get());
                if (value == nullptr) { return {}; }
                return (std::reference_wrapper<T>(*value));
            }
        }
        return {};
    };
    EntityType getEntityType() const noexcept;
    bool       getEnabledValue() const noexcept;
    void       setEnabledValue(const bool value) noexcept;

  private:
    const EntityType                        type_;
    bool                                    is_enabled_ = true;
    std::vector<std::unique_ptr<Component>> components_ = {};
};
