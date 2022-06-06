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

void SoundManager::play() noexcept
{
    PlaySound(sound_);
    isPlaying = true;
}

void SoundManager::setVolume(float volume) noexcept
{
    SetSoundVolume(sound_, volume);
}

void SoundManager::stop() noexcept
{
    StopSound(sound_);
    isPlaying = false;
}

bool SoundManager::getIsPlaying() const noexcept
{
    return isPlaying;
}