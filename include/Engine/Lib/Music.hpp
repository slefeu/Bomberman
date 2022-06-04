/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Music
*/

#pragma once
#include <string>

#include "raylib.h"

class MusicManager
{
  public:
    MusicManager(const std::string& path) noexcept;
    MusicManager(const MusicManager& other) noexcept = default;
    MusicManager(MusicManager&& other) noexcept      = default;
    ~MusicManager() noexcept                         = default;

    MusicManager& operator=(const MusicManager& rhs) noexcept = default;
    MusicManager& operator=(MusicManager&& rhs) noexcept = default;

    void play() const noexcept;
    void update() noexcept;
    void unload() noexcept;

  protected:
  private:
    Music music_;
};