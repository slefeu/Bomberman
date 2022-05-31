#include "Shortcuts.hpp"

#pragma once

class Component
{
  public:
    Component() noexcept                       = default;
    Component(const Component& other) noexcept = default;
    Component(Component&& other) noexcept      = default;
    virtual ~Component() noexcept              = default;

    Component& operator=(const Component& rhs) noexcept = default;
    Component& operator=(Component&& rhs) noexcept      = default;

    virtual ComponentType getComponentType() const noexcept = 0;

  protected:
  private:
};