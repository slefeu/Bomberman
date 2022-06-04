/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Render
*/

#include "Render.hpp"

Render::Render() noexcept
    : color_(Colors::C_WHITE)
{
}

void Render::display(const Transform3D& transform) noexcept
{
    auto color = color_.getColor();

    if (type == RenderType::R_3DMODEL) {
        DrawModel(model_->get()->model,
            transform.getPosition(),
            transform.getScale(),
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_3DMODEL_ROTATE) {
        Vector3 rotationAxis  = transform.getRotationAxis();
        float   rotationAngle = transform.getRotationAngle();
        float   scale         = transform.getScale();
        DrawModelEx(model_->get()->model,
            transform.getPosition(),
            rotationAxis,
            rotationAngle,
            { scale, scale, scale },
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_CUBE) {
        DrawCubeV(transform.getPosition(),
            transform.getSize(),
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_WIRED_CUBE) {
        DrawCubeWiresV(transform.getPosition(),
            transform.getSize(),
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_ANIMATE) {
        model_->get()->updateAnimation();
        Vector3 rotationAxis  = transform.getRotationAxis();
        float   rotationAngle = transform.getRotationAngle();
        float   scale         = transform.getScale();
        DrawModelEx(model_->get()->model,
            transform.getPosition(),
            rotationAxis,
            rotationAngle,
            { scale, scale, scale },
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
}

void Render::setRenderType(const RenderType& type) noexcept
{
    this->type = type;
}

void Render::setModel(std::unique_ptr<Model3D>* model) noexcept
{
    model_ = model;
}

void Render::setColor(const std::array<unsigned char, 3>& color) noexcept
{
    color_.setColor(color);
}

RenderType Render::getRenderType() const noexcept
{
    return (type);
}

ComponentType Render::getComponentType() const noexcept
{
    return (TYPE);
}