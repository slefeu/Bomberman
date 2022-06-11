/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** AudioDevice
*/

#include "AudioDevice.hpp"

void AudioDevice::initialize() noexcept
{
    InitAudioDevice();
}

void AudioDevice::update(const Scene& scene) noexcept
{
    scene.updateMusic();
}

void AudioDevice::close() noexcept
{
    CloseAudioDevice();
}

void AudioDevice::setMusic(float value) noexcept
{
    SetMasterVolume(value / 100);
}