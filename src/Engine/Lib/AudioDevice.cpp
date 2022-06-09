/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** AudioDevice
*/

#include "AudioDevice.hpp"

AudioDevice::AudioDevice() noexcept
{
    InitAudioDevice();
}

AudioDevice::~AudioDevice() noexcept
{
    CloseAudioDevice();
}

void AudioDevice::update(const Scene& scene) noexcept
{
    scene.updateMusic();
}
