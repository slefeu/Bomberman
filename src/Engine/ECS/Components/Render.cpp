/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Render
*/

#include "Render.hpp"

Render::Render(Model3D& model) noexcept
    : color_(Colors::C_WHITE)
    , model_(model)
    , animation_()
{
}

Render::~Render() noexcept {}

void Render::display(const Transform3D& transform) noexcept
{
    auto     color = color_.getColor();
    Vector3D pos   = transform.getPosition();
    Vector3D rot   = transform.getRotationAxis();
    float    scale = transform.getScale();

    if (type == RenderType::R_3DMODEL) {
        model_.draw(pos, scale, color);
    } else if (type == RenderType::R_3DMODEL_ROTATE) {
        float rotationAngle = transform.getRotationAngle();
        model_.draw(pos, rot, rotationAngle, scale, color);
    } else if (type == RenderType::R_ANIMATE) {
        animation_.updateAnimation(model_);
        float rotationAngle = transform.getRotationAngle();
        model_.draw(pos, rot, rotationAngle, scale, color);
    }
}

void Render::setRenderType(const RenderType& type) noexcept
{
    this->type = type;
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

void Render::displayModel(const Transform3D& transform, const Vector3D& pos) noexcept
{
    auto axis  = transform.getRotationAxis();
    auto angle = transform.getRotationAngle();

    displayModelV(transform, pos, axis, angle);
}

void Render::displayModelV(
    const Transform3D& transform, const Vector3D& pos, const Vector3D& axis, float angle) noexcept
{
    if (type == RenderType::R_ANIMATE) {
        std::array<unsigned char, 3> color = { 255, 255, 255 };
        model_.draw(pos, axis, angle, transform.getScale(), color);
    }
}

Animation& Render::getAnimation() noexcept
{
    return animation_;
}

Model3D& Render::getModel() noexcept
{
    return model_;
}