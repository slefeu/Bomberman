/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Music
*/

#include "Music.hpp"

MusicManager::MusicManager(const std::string& path) noexcept
    : music_(LoadMusicStream(path.c_str()))
{
    setVolume(0.8f);
}

void MusicManager::unload() noexcept
{
    UnloadMusicStream(music_);
}

void MusicManager::play() noexcept
{
    PlayMusicStream(music_);
    isPlaying = true;
}

void MusicManager::update() noexcept
{
    UpdateMusicStream(music_);
}

void MusicManager::setVolume(float volume) noexcept
{
    SetMusicVolume(music_, volume);
}

void MusicManager::stop() noexcept
{
    StopMusicStream(music_);
    isPlaying = false;
}

bool MusicManager::getIsPlaying() const noexcept
{
    return isPlaying;
}