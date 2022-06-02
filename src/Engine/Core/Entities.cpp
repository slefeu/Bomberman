/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Entities
*/

#include "Entities.hpp"

Entities::Entities(const EntityType& type) noexcept
    : type_(type)
{
    addComponent(Transform3D());
    addComponent(Render());
}

std::vector<std::unique_ptr<Component>>& Entities::getComponents() noexcept
{
    return (components_);
}

EntityType Entities::getEntityType() const noexcept
{
    return (type_);
}

bool Entities::getEnabledValue() const noexcept
{
    return (is_enabled_);
}

void Entities::setEnabledValue(const bool value) noexcept
{
    is_enabled_ = value;
}
