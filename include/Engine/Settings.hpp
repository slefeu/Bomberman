/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

class Settings
{
  public:
    Settings(int fps, int winWidth, int winHeight, int nbPlayer) noexcept;
    ~Settings() noexcept = default;

  public:
    int fps;
    int winWidth;
    int winHeight;
    int nbPlayer;
};

#endif /* !SETTINGS_HPP_ */
