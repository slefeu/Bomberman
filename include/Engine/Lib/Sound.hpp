/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Sound
*/

#pragma once
#include <string>

#include "raylib.h"

class SoundManager
{
  public:
    explicit SoundManager(const std::string& path) noexcept;
    SoundManager(const SoundManager& other) noexcept = default;
    SoundManager(SoundManager&& other) noexcept      = default;
    ~SoundManager() noexcept                         = default;

    SoundManager& operator=(const SoundManager& rhs) noexcept = default;
    SoundManager& operator=(SoundManager&& rhs) noexcept      = default;

    void unload() noexcept;
    void play() noexcept;
    void setVolume(float volume) noexcept;
    void stop() noexcept;
    bool getIsPlaying() const noexcept;

  protected:
  private:
    Sound sound_;
    bool  isPlaying;
};