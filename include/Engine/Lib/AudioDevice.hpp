/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** AudioDevice
*/

#pragma once
#include "Scene.hpp"

class AudioDevice
{
  public:
    AudioDevice() noexcept;
    AudioDevice(const AudioDevice& other) noexcept = default;
    AudioDevice(AudioDevice&& other) noexcept      = default;
    ~AudioDevice() noexcept;

    AudioDevice& operator=(const AudioDevice& rhs) noexcept = default;
    AudioDevice& operator=(AudioDevice&& rhs) noexcept = default;

    void update(const Scene& scene) noexcept;

  protected:
  private:
};
