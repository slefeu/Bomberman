/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** model_3D
*/

#include "Model3D.hpp"

Model3D::Model3D(const std::string_view& path, const std::string_view& texture_Path) noexcept
    : model_(LoadModel(path.data()))
    , texture_(LoadTexture(texture_Path.data()))
{
    model_.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture_;
}

Model3D::~Model3D() noexcept
{
    this->unload();
}

void Model3D::unload() noexcept
{
    if (!unloaded_) {
        UnloadTexture(texture_);
        UnloadModel(model_);
        unloaded_ = true;
    }
}
void Model3D::draw(const Vector3D&      pos,
    float                               scale,
    const std::array<unsigned char, 3>& color_infos) const noexcept
{
    Color color = { color_infos[0], color_infos[1], color_infos[2], 255 };
    DrawModel(model_, { pos.x, pos.y, pos.z }, scale, color);
}

void Model3D::draw(const Vector3D&      pos,
    const Vector3D&                     rotation,
    float                               rotation_angle,
    float                               scale,
    const std::array<unsigned char, 3>& color_infos) const noexcept
{
    Color color = { color_infos[0], color_infos[1], color_infos[2], 255 };
    DrawModelEx(model_,
        { pos.x, pos.y, pos.z },
        { rotation.x, rotation.y, rotation.z },
        rotation_angle,
        { scale, scale, scale },
        color);
}

void Model3D::update(ModelAnimation animation, int frame_counter)
{
    UpdateModelAnimation(model_, animation, frame_counter);
}