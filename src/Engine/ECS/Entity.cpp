/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Entity
*/

#include "Entity.hpp"

std::vector<std::unique_ptr<Component>>& Entity::getComponents() noexcept
{
    return (components_);
}

bool Entity::getEnabledValue() const noexcept
{
    return (is_enabled_);
}

void Entity::setEnabledValue(bool value) noexcept
{
    is_enabled_ = value;
}
