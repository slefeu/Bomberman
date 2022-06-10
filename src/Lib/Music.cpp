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
    setVolume(0.5f);
}

MusicManager::MusicManager(MusicManager&& other) noexcept
    : music_(std::move(other.music_))
    , isPlaying_(other.isPlaying_)
{
    setVolume(0.5f);
    other.unloaded_ = true;
}

MusicManager& MusicManager::operator=(MusicManager&& rhs) noexcept
{
    music_         = std::move(rhs.music_);
    isPlaying_     = rhs.isPlaying_;
    rhs.isPlaying_ = false;
    rhs.unloaded_  = true;
    return *(this);
}

MusicManager::~MusicManager() noexcept
{
    this->unload();
}

void MusicManager::unload() noexcept
{
    if (!unloaded_) {
        UnloadMusicStream(music_);
        unloaded_ = true;
    }
}

void MusicManager::play() noexcept
{
    isPlaying_ = true;
    PlayMusicStream(music_);
}

void MusicManager::update() const noexcept
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
    return (isPlaying_);
}