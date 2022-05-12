/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Box
*/

#ifndef Wall_HPP_
#define Wall_HPP_

#include "Crate.hpp"

class Wall : public Crate
{
  public:
    Wall(Vector3 pos) noexcept;
    ~Wall() noexcept = default;
    void display() noexcept;
};

#endif /* !Wall_HPP_ */
