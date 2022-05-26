#include "Render.hpp"

void Render::display(Transform3D& transform) noexcept
{
    if (type == RenderType::R_3DMODEL) {
        DrawModel(model->get()->model, transform.getPosition(), transform.getScale(), WHITE);
        return;
    }
    if (type == RenderType::R_3DMODEL_ROTATE) {
        Vector3 rotationAxis  = transform.getRotationAxis();
        float   rotationAngle = transform.getRotationAngle();
        float   scale         = transform.getScale();
        DrawModelEx(model->get()->model, transform.getPosition(), rotationAxis, rotationAngle, { scale, scale, scale }, WHITE);
        return;
    }
    if (type == RenderType::R_CUBE) {
        DrawCubeV(transform.getPosition(), transform.getSize(), color);
        return;
    }
    if (type == RenderType::R_WIRED_CUBE) {
        DrawCubeWiresV(transform.getPosition(), transform.getSize(), color);
        return;
    }
}

void Render::setRenderType(RenderType type) noexcept
{
    this->type = type;
}

void Render::setModel(std::unique_ptr<Model3D>* model) noexcept
{
    this->model = model;
}

void Render::setColor(Color color) noexcept
{
    this->color = color;
}

RenderType Render::getRenderType() const noexcept
{
    return this->type;
}