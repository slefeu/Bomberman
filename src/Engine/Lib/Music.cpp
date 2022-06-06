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
    isPlaying_ = true;
    PlayMusicStream(music_);
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
    isPlaying_ = false;
    StopMusicStream(music_);
}

bool MusicManager::isPlaying() const noexcept
{
    return isPlaying_;
}