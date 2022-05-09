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
    Scene() noexcept = default;
    virtual ~Scene() noexcept = default;
    virtual void placeCamera(Cameraman& camera) noexcept = 0;
    virtual void display(void) noexcept = 0;
    virtual void action() noexcept = 0;

  public:
    Vector3 cameraPosition;
};

#endif /* !SCENE_HPP_ */
