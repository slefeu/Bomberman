/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Window
*/

#pragma once
#include "Scene.hpp"

class WindowManager
{
  public:
    WindowManager() noexcept                           = default;
    WindowManager(const WindowManager& other) noexcept = delete;
    WindowManager(WindowManager&& other) noexcept      = delete;
    ~WindowManager() noexcept;

    WindowManager& operator=(const WindowManager& rhs) noexcept = delete;
    WindowManager& operator=(WindowManager&& rhs) noexcept = delete;

    void launch(int width, int height, int fps) const noexcept;
    void display(Scene& scene, const Cameraman& camera) noexcept;
    bool isExit() noexcept;
    int  getWidth() const noexcept;
    int  getHeight() const noexcept;

  protected:
  private:
};
