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
    Home() noexcept;
    ~Home() noexcept = default;
    void placeCamera(Cameraman& camera) noexcept;
    void display(void) noexcept;
    void action() noexcept;
};

#endif /* !HOME_HPP_ */
