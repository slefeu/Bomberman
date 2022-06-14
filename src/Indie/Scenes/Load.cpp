/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** Load
*/

#include "Load.hpp"

#include <exception>
#include <filesystem>
#include <iostream>
#include <string>

#include "Bomberman.hpp"

Load::Load(Core& core_ref) noexcept
    : loop_music_(MUSIC)
    , core_entry_(core_ref)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH, 0, 0, 1.1)
    , title_(TITLE_PATH, 30, 30, 0.7)
    , title_text_(FONT_PATH, "Pick a save :", 0, 0)
{
    title_text_.setTextSize(40);
    title_text_.setPosition(
        core_entry_.getWindow().getWidth() / 2, core_entry_.getWindow().getHeight() / 9);
    for (int i = 0; i < 3; i++) { load_names_.emplace_back(FONT_PATH, "Test", 40, 40); }
    createButtons();
    createIllustrations();
}

void Load::createTexts() noexcept
{
    load_names_.emplace_back(FONT_PATH, "No Save", 0, 0); // à changer avec les noms de tes saves
    load_names_.emplace_back(FONT_PATH, "No Save", 0, 0);
    load_names_.emplace_back(FONT_PATH, "No Save", 0, 0);
}

void Load::createIllustrations() noexcept
{
    int width  = core_entry_.getWindow().getWidth();
    int height = core_entry_.getWindow().getHeight();

    illustrations_.emplace_back(WHITE_IMG, width / 6 - 10, height / 4 + 30);
    illustrations_.emplace_back(
        RED_IMG, width / 6 + (490 * illustrations_.size()), height / 4 + 30);
    illustrations_.emplace_back(
        BLACK_IMG, width / 6 + (495 * illustrations_.size()), height / 4 + 30);
}

void Load::drawIllustrations() const noexcept
{
    for (auto& it : illustrations_) { it.draw(); }
}

void Load::createButtons() noexcept
{
    int         width  = core_entry_.getWindow().getWidth();
    int         height = core_entry_.getWindow().getHeight();
    std::string fileName;

    getSavesNames();
    for (int i = 0; i < 3; i++) {
        (save_names[i].compare("No Save")) ? fileName = save_names[i].substr(5)
                                           : fileName = save_names[i];
        load_names_[i].setText(fileName);
        if (save_names[i].compare("No Save"))
            buttons_.emplace_back(BUTTON_PATH,
                width / 6 + (500 * buttons_.size()),
                height - (height / 4),
                std::function<void(void)>([this, i](void) {
                    core_entry_.getData().setTryToLoad(save_names[i]);
                    return core_entry_.switchScene(bomberman::SceneType::GAME);
                }),
                FONT_PATH,
                load_names_[i].getText(),
                20,
                0);
        else
            buttons_.emplace_back(BUTTON_PATH,
                width / 6 + (500 * buttons_.size()),
                height - (height / 4),
                std::function<void(void)>([this, i](void) { return; }),
                FONT_PATH,
                load_names_[i].getText(),
                20,
                0);
    }
    buttons_.emplace_back("assets/textures/selection/close.png",
        width / 4 + 1200,
        height / 10,
        std::function<void(void)>(
            [this](void) { core_entry_.switchScene(bomberman::SceneType::MENU); }),
        "assets/fonts/menu.ttf",
        "");
}

void Load::getSavesNames() noexcept
{
    int nbSave = 0;

    try {
        for (const auto& entry : std::filesystem::directory_iterator(SAVE_PATH)) {
            if (nbSave >= 3) break;
            save_names.emplace_back(entry.path());
            nbSave++;
        }

    } catch (std::exception err) {
        std::filesystem::create_directory("Save");
        getSavesNames();
    }
    while (save_names.size() < 3) { save_names.emplace_back("No Save"); }
}

void Load::switchAction() noexcept
{
    core_entry_.getCameraman().tpTo(
        { 4.0f, 2.0f, 1.5f }, { 0.0f, 1.0f, 1.5f }, { 0.0f, 2.0f, 0.0f });
}

void Load::drawButtons() const noexcept
{
    for (auto& it : buttons_) { it.draw(); }
}

void Load::action() noexcept
{
    if (controller_.isGamepadConnected(0)) {
        if (controller_.isGamepadButtonPressed(0, G_Button::G_DPAD_UP))
            button_index_ = (button_index_ - 1) % buttons_.size();
        if (controller_.isGamepadButtonPressed(0, G_Button::G_DPAD_DOWN))
            button_index_ = (button_index_ + 1) % buttons_.size();
        if (controller_.isGamepadButtonPressed(0, G_Button::G_B)) buttons_[button_index_].action();
        for (auto& it : buttons_) it.setState(0);
        buttons_[button_index_].setState(1);
    } else {
        for (auto& it : buttons_)
            if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    }
}

void Load::playMusic() noexcept
{
    loop_music_.play();
}

void Load::updateMusic() const noexcept
{
    loop_music_.update();
}

ColorManager Load::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void Load::SystemDisplay() noexcept
{
    background_.draw({ 255, 255, 255, 175 });
    title_.draw();
    FpsHandler::draw(10, 10);
    title_text_.draw();
    drawButtons();
    drawIllustrations();
}
