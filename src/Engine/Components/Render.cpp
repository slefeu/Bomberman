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

Render::~Render() noexcept
{
    if (!anims) return;

    for (unsigned int i = 0; i < animsCount; i++) UnloadModelAnimation(anims[i]);
    RL_FREE(anims);
}

void Render::display(const Transform3D& transform) noexcept
{
    auto color = color_.getColor();

    Vector3D pos  = transform.getPosition();
    Vector3D rot  = transform.getRotationAxis();
    Vector3D size = transform.getSize();

    if (type == RenderType::R_3DMODEL) {
        DrawModel(model_->get()->model,
            { pos.x, pos.y, pos.z },
            transform.getScale(),
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_3DMODEL_ROTATE) {
        float rotationAngle = transform.getRotationAngle();
        float scale         = transform.getScale();
        DrawModelEx(model_->get()->model,
            { pos.x, pos.y, pos.z },
            { rot.x, rot.y, rot.z },
            rotationAngle,
            { scale, scale, scale },
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_CUBE) {
        DrawCubeV({ pos.x, pos.y, pos.z },
            { size.x, size.y, size.z },
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_WIRED_CUBE) {
        DrawCubeWiresV({ pos.x, pos.y, pos.z },
            { size.x, size.y, size.z },
            (Color){ color[0], color[1], color[2], 255 });
        return;
    }
    if (type == RenderType::R_ANIMATE) {
        updateAnimation();
        float rotationAngle = transform.getRotationAngle();
        float scale         = transform.getScale();
        DrawModelEx(model_->get()->model,
            { pos.x, pos.y, pos.z },
            { rot.x, rot.y, rot.z },
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

void Render::addAnimation(std::string path) noexcept
{
    anims = LoadModelAnimations(path.c_str(), &animsCount);
}

void Render::updateAnimation() noexcept
{
    if (anims == nullptr) return;
    if (isAnimated) {
        animFrameCounter += 1.0f * skipFrame;
        UpdateModelAnimation(model_->get()->model, anims[animationId], animFrameCounter);
        if (animFrameCounter >= anims[animationId].frameCount) animFrameCounter = 0;
    }
}

void Render::resetAnimation(int frame) noexcept
{
    if (anims == nullptr) return;
    animFrameCounter = frame;
    UpdateModelAnimation(model_->get()->model, anims[animationId], animFrameCounter);
}

void Render::setSkipFrame(int frame) noexcept
{
    skipFrame = frame;
}

void Render::setAnimationId(int id) noexcept
{
    animationId = id;
}

void Render::displayModel(const Transform3D& transform, Vector3D pos) noexcept
{
    auto axis  = transform.getRotationAxis();
    auto angle = transform.getRotationAngle();

    displayModelV(transform, pos, axis, angle);
}

void Render::displayModelV(
    const Transform3D& transform, Vector3D pos, Vector3D axis, float angle) noexcept
{
    if (model_ == nullptr) return;

    if (type == RenderType::R_ANIMATE) {
        updateAnimation();
        float scale = transform.getScale();
        DrawModelEx(model_->get()->model,
            { pos.x, pos.y, pos.z },
            { axis.x, axis.y, axis.z },
            angle,
            { scale, scale, scale },
            (Color){ 255, 255, 255, 255 });
        return;
    }
}