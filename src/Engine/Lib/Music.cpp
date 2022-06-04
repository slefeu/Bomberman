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
}

void MusicManager::unload() noexcept
{
    UnloadMusicStream(music_);
}

void MusicManager::play() const noexcept
{
    PlayMusicStream(music_);
}

void MusicManager::update() noexcept
{
    UpdateMusicStream(music_);
}