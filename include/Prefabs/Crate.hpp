/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Crate
*/

#ifndef CRATE_HPP_
#define CRATE_HPP_

#include "Box.hpp"

class Crate : public Box
{
  public:
    Crate(Vector3 pos, std::unique_ptr<Render3D>* model) noexcept;
    ~Crate() noexcept = default;
    void display() noexcept;
};

#endif /* !CRATE_HPP_ */
