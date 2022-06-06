/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Sound
*/

#include "Sound.hpp"

SoundManager::SoundManager(const std::string& path) noexcept
    : sound_(LoadSound(path.c_str()))
{
    setVolume(1.0f);
}

void SoundManager::unload() noexcept
{
    UnloadSound(sound_);
}

void SoundManager::play() const noexcept
{
    PlaySound(sound_);
}

void SoundManager::setVolume(float volume) noexcept
{
    SetSoundVolume(sound_, volume);
}