/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Splash
*/

#include "Splash.hpp"

#include "DeltaTime.hpp"

Splash::Splash(Core& core_ref) noexcept
    : Scene()
    , core_entry_(core_ref)
    , background_color_(Colors::C_BLACK)
    , timer(4.3f)
    , opacity_(255)
{
}

void Splash::switchAction() noexcept {}

void Splash::action() noexcept
{
    timer.updateTimer();

    if (timer.isTimerDone()) core_entry_.switchScene(bomberman::SceneType::MENU);
}

void Splash::playMusic() noexcept {}

void Splash::updateMusic() const noexcept {}

ColorManager Splash::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void Splash::SystemDisplay() noexcept
{
    FpsHandler::draw(10, 10);

    auto& sprites = core_entry_.getData().getSprites();
    if (sprites.size() == 0) return;
    sprites[0]->draw({ 255, 255, 255, opacity_ });
    if (opacity_ > 0) opacity_ -= 15 * DeltaTime::getDeltaTime();
}