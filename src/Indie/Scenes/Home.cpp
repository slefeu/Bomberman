/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

Home::Home(Core& core_ref) noexcept
    : Scene()
    , loop_music_(MENU_MUSIC)
    , core_entry_(core_ref)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH, 0, 0, 1.1)
    , title_(TITLE_PATH, 30, 30)
{
    createButtons();
    createTexts();
}

void Home::switchAction() noexcept
{
    core_entry_.getCameraman().moveTo(
        { 20.0f, 50.0f, 30.0f }, { 0.0f, 0.0f, 1.0f }, { 0.0f, 2.0f, 0.0f });
}

void Home::createTexts() noexcept
{
    int width = core_entry_.getWindow().getWidth();

    settings_texts_.emplace_back(
        FONT_PATH, "Music :", width / 2 + 40, width / 8 + (150 * buttons_.size() - 10));
    settings_texts_.emplace_back(
        FONT_PATH, "Fps : ", width / 2 + 40, width / 8 + (150 * buttons_.size() + 70));
    settings_texts_.emplace_back(FONT_PATH,
        std::to_string(core_entry_.getWindow().getMusicPercentage()),
        width / 2 + 200,
        width / 8 + (150 * buttons_.size() - 10));
    settings_texts_.emplace_back(FONT_PATH,
        std::to_string(static_cast<int>(core_entry_.getWindow().getFps())),
        width / 2 + 200,
        width / 8 + (150 * buttons_.size() + 70));

    for (auto& it : settings_texts_) { it.invertDisplay(); }
}

void Home::createButtons() noexcept
{
    int width = core_entry_.getWindow().getWidth();

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 2,
        width / 8,
        std::function<void(void)>(
            [this](void) { core_entry_.switchScene(bomberman::SceneType::SELECT); }),
        FONT_PATH,
        "Play");

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 2,
        (width / 8) + (150 * buttons_.size()),
        std::function<void(void)>(
            [this](void) { core_entry_.switchScene(bomberman::SceneType::LOAD); }),
        FONT_PATH,
        "Load");

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 2,
        width / 8 + (150 * buttons_.size()),
        std::function<void(void)>([this](void) { core_entry_.setExit(true); }),
        FONT_PATH,
        "Exit",
        30,
        0);

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 2,
        width / 8 + (150 * buttons_.size()),
        std::function<void(void)>([this](void) {
            for (auto& it : settings_) { it.invertDisplay(); }
            for (auto& it : settings_texts_) { it.invertDisplay(); }
        }),
        FONT_PATH,
        "Settings",
        50,
        0);

    settings_.emplace_back("assets/textures/selection/left.png",
        width / 2 - 40,
        width / 8 + (150 * (buttons_.size()) - 30),
        std::function<void(void)>([this](void) {
            core_entry_.getWindow().decreaseMusic();
            settings_texts_[2].setText(
                std::to_string(core_entry_.getWindow().getMusicPercentage()));
        }),
        FONT_PATH,
        "",
        0.2f);

    settings_.emplace_back("assets/textures/selection/right.png",
        width / 2 + 300,
        width / 8 + (150 * (buttons_.size()) - 30),
        std::function<void(void)>([this](void) {
            core_entry_.getWindow().increaseMusic();
            settings_texts_[2].setText(
                std::to_string(core_entry_.getWindow().getMusicPercentage()));
        }),
        FONT_PATH,
        "",
        0.2f);

    settings_.emplace_back("assets/textures/selection/left.png",
        width / 2 - 40,
        width / 8 + (150 * (buttons_.size()) + 50),
        std::function<void(void)>([this](void) {
            core_entry_.getWindow().decreaseFps();
            settings_texts_[3].setText(
                std::to_string(static_cast<int>(core_entry_.getWindow().getFps())));
        }),
        FONT_PATH,
        "",
        0.2f);

    settings_.emplace_back("assets/textures/selection/right.png",
        width / 2 + 300,
        width / 8 + (150 * (buttons_.size()) + 50),
        std::function<void(void)>([this](void) {
            core_entry_.getWindow().increaseFps();
            settings_texts_[3].setText(
                std::to_string(static_cast<int>(core_entry_.getWindow().getFps())));
        }),
        FONT_PATH,
        "",
        0.2f);
    for (auto& it : settings_) { it.invertDisplay(); }
}

void Home::action() noexcept
{
    for (auto& it : buttons_)
        if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    for (auto& it : settings_)
        if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
}

void Home::playMusic() noexcept
{
    loop_music_.play();
}

void Home::updateMusic() const noexcept
{
    loop_music_.update();
}

void Home::drawButtons() const noexcept
{
    for (auto& it : buttons_) { it.draw(); }
    for (auto& it : settings_) { it.draw(); }
}

ColorManager Home::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void Home::SystemDisplay() noexcept
{
    background_.draw({ 255, 255, 255, 175 });
    title_.draw();
    FpsHandler::draw(10, 10);
    drawButtons();
    for (auto& it : settings_texts_) { it.draw(); }
}