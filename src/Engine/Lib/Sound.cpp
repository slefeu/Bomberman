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
    setVolume(1);
}

SoundManager::SoundManager(SoundManager&& other) noexcept
    : sound_(std::move(other.sound_))
{
    other.unloaded_ = true;
    other.setVolume(1);
}

SoundManager& SoundManager::operator=(SoundManager&& rhs) noexcept
{
    sound_        = std::move(rhs.sound_);
    rhs.unloaded_ = true;
    return *(this);
}

SoundManager::~SoundManager() noexcept
{
    this->unload();
}

void SoundManager::unload() noexcept
{
    if (!unloaded_) {
        UnloadSound(sound_);
        unloaded_ = true;
    }
}

void SoundManager::play() const noexcept
{
    PlaySound(sound_);
}

void SoundManager::setVolume(float value) noexcept
{
    SetSoundVolume(sound_, value);
}