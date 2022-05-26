/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Render.cpp
*/

#pragma once

#include <memory>

#include "Model3D.hpp"
#include "Transform3D.hpp"

enum class RenderType {
    R_3DMODEL,
    R_3DMODEL_ROTATE,
    R_CUBE,
    R_WIRED_CUBE,
    R_NONE,
};

class Render
{
  private:
    RenderType                type  = RenderType::R_NONE;
    std::unique_ptr<Model3D>* model = nullptr;
    Color                     color = GREEN;

  public:
    Render() noexcept                    = default;
    ~Render() noexcept                   = default;
    Render(const Render& other) noexcept = delete;
    Render(Render&& other) noexcept      = delete;

    Render& operator=(const Render& rhs) noexcept = delete;
    Render& operator=(Render&& rhs) noexcept      = delete;

    void       display(Transform3D& transform) noexcept;
    void       setRenderType(RenderType type) noexcept;
    void       setModel(std::unique_ptr<Model3D>* model) noexcept;
    void       setColor(Color color) noexcept;
    RenderType getRenderType() const noexcept;
};