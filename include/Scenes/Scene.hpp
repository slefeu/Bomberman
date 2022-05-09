/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Scene
*/

#ifndef SCENE_HPP_
#define SCENE_HPP_

#include "Cameraman.hpp"

class Scene
{
  public:
    Vector3 cameraPosition;
    Vector3 cameraTarget;
    Vector3 cameraUp;

  public:
    Scene() noexcept                                     = default;
    virtual ~Scene() noexcept                            = default;
    virtual void resetCamera(Cameraman& camera) noexcept = 0;
    virtual void display3D(void) noexcept                = 0;
    virtual void display2D(void) noexcept                = 0;
    virtual void action() noexcept                       = 0;
};

#endif /* !SCENE_HPP_ */
