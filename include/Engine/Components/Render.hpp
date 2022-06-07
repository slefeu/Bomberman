/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Render.cpp
*/

#pragma once

#include <memory>

#include "Color.hpp"
#include "Model3D.hpp"
#include "Transform3D.hpp"

enum class RenderType {
    R_3DMODEL,
    R_3DMODEL_ROTATE,
    R_CUBE,
    R_WIRED_CUBE,
    R_ANIMATE,
    R_NONE,
};

class Render : public Component
{
  public:
    Render() noexcept;
    ~Render() noexcept;
    Render(const Render& other) noexcept = default;
    Render(Render&& other) noexcept      = default;

    Render& operator=(const Render& rhs) noexcept = default;
    Render& operator=(Render&& rhs) noexcept      = default;

    void          display(const Transform3D& transform) noexcept;
    void          setRenderType(const RenderType& type) noexcept;
    void          setModel(std::unique_ptr<Model3D>* model) noexcept;
    void          setColor(const std::array<unsigned char, 3>& color) noexcept;
    RenderType    getRenderType() const noexcept;
    ComponentType getComponentType() const noexcept;

    void addAnimation(std::string path) noexcept;
    void updateAnimation() noexcept;
    void resetAnimation(int frame) noexcept;
    void setSkipFrame(int frame) noexcept;
    void setAnimationId(int id) noexcept;

    void displayModel(const Transform3D& transform, Vector3 pos) noexcept;
    void displayModelV(
        const Transform3D& transform, Vector3 pos, Vector3 axis, float angle) noexcept;

    static constexpr ComponentType TYPE = ComponentType::RENDER;

  private:
    RenderType                type             = RenderType::R_NONE;
    std::unique_ptr<Model3D>* model_           = nullptr;
    ColorManager              color_           = Colors::C_WHITE;
    ModelAnimation*           anims            = nullptr;
    int                       animFrameCounter = 0;
    unsigned int              animsCount       = 0;
    bool                      isAnimated       = true;
    int                       skipFrame        = 1;
    int                       animationId      = 0;
};
