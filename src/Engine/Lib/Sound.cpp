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
}

void SoundManager::unload() noexcept
{
    UnloadSound(sound_);
}

void SoundManager::play() const noexcept
{
    PlaySound(sound_);
}