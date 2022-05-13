/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#ifndef HOME_HPP_
#define HOME_HPP_

#include "Scene.hpp"

class Home : public Scene
{
  public:
    Home(GameData* data) noexcept;
    ~Home() noexcept = default;
    void resetCamera(Cameraman& camera) noexcept;
    void display3D(void) noexcept;
    void display2D(void) noexcept;
    void action(Cameraman& camera) noexcept;
};

#endif /* !HOME_HPP_ */
