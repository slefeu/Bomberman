/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Render.cpp
*/

#pragma once

#include <memory>
#include <string_view>

#include "Color.hpp"
#include "Model3D.hpp"
#include "Transform3D.hpp"
#include "Vector.hpp"

enum class RenderType {
    R_3DMODEL,
    R_3DMODEL_ROTATE,
    R_ANIMATE,
    R_NONE,
};

class Render : public Component
{
  public:
    Render(Model3D& model) noexcept;
    Render(const Render& other) noexcept = default;
    Render(Render&& other) noexcept      = default;
    ~Render() noexcept;

    Render& operator=(const Render& rhs) noexcept = delete;
    Render& operator=(Render&& rhs) noexcept = delete;

    void          display(const Transform3D& transform) noexcept;
    void          setRenderType(const RenderType& type) noexcept;
    void          setColor(const std::array<unsigned char, 3>& color) noexcept;
    RenderType    getRenderType() const noexcept;
    ComponentType getComponentType() const noexcept;

    void addAnimation(const std::string_view& path) noexcept;
    void updateAnimation() noexcept;
    void resetAnimation(int frame) noexcept;
    void setSkipFrame(int frame) noexcept;
    void setAnimationId(int id) noexcept;

    void displayModel(const Transform3D& transform, const Vector3D& pos) noexcept;
    void displayModelV(const Transform3D& transform,
        const Vector3D&                   pos,
        const Vector3D&                   axis,
        float                             angle) noexcept;

    static constexpr ComponentType TYPE = ComponentType::RENDER;

  private:
    RenderType      type = RenderType::R_NONE;
    Model3D&        model_;
    ColorManager    color_            = Colors::C_WHITE;
    ModelAnimation* animations_       = nullptr;
    unsigned int    frame_counter_    = 0;
    unsigned int    animations_count_ = 0;
    unsigned int    skip_frame_       = 1;
    unsigned int    animation_id_     = 0;
    bool            is_animated_      = true;
};
