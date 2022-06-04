/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity(const EntityType& type) noexcept
    : type_(type)
{
    addComponent(Transform3D());
    addComponent(Render());
}

std::vector<std::unique_ptr<Component>>& Entity::getComponents() noexcept
{
    return (components_);
}

EntityType Entity::getEntityType() const noexcept
{
    return (type_);
}

bool Entity::getEnabledValue() const noexcept
{
    return (is_enabled_);
}

void Entity::setEnabledValue(const bool value) noexcept
{
    is_enabled_ = value;
}
