/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Window
*/

#pragma once
#include "AudioDevice.hpp"
#include "Fps.hpp"
#include "Scene.hpp"

class WindowManager
{
  public:
    WindowManager(int width, int height, int fps) noexcept;
    WindowManager(const WindowManager& other) noexcept = delete;
    WindowManager(WindowManager&& other) noexcept      = delete;
    ~WindowManager() noexcept;

    WindowManager& operator=(const WindowManager& rhs) noexcept = delete;
    WindowManager& operator=(WindowManager&& rhs) noexcept = delete;

    void display(Scene& scene, const Cameraman& camera) noexcept;
    bool isExit() noexcept;

    int   getWidth() const noexcept;
    int   getHeight() const noexcept;
    float getFps() const noexcept;
    void  setFps(float value) noexcept;
    void  resetHeight() noexcept;
    void  resetWidth() noexcept;
    void  increaseFps() noexcept;
    void  decreaseFps() noexcept;

  protected:
  private:
    int                  width_;
    int                  height_;
    float                fps_;
    int                  index_        = 1;
    std::array<float, 4> possible_fps_ = { 30, 60, 90, 120 };
};
