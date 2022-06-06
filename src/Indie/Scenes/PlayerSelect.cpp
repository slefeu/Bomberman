/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** PlayerSelect
*/

#include "PlayerSelect.hpp"

PlayerSelect::PlayerSelect(GameData* data, Core& core_ref) noexcept
    : Scene()
    , loop_music_(MUSIC)
    , core_entry_(core_ref)
    , data_(data)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH, 0, 0, 1.1)
    , title_(TITLE_PATH, 30, 30)
    , choose_(SELECT, "Select players", data_->winWidth / 2, data_->winHeight / 6)
{
    choose_.setTextColor(Colors::C_BLACK);
    choose_.setTextSize(40);
    createButtons();
}

PlayerSelect::~PlayerSelect() noexcept
{
    loop_music_.unload();
    background_.unload();
    title_.unload();
}

void PlayerSelect::display3D() noexcept
{
    float nbPlayers = 0;
    for (auto& player : data_->players) {
        Vector3 position = { 0, 0, 5 - data_->nbPlayer + nbPlayers };
        player->displayModel(position);
        nbPlayers++;
    }
}

void PlayerSelect::display2D() noexcept
{
    FpsHandler::draw(10, 10);
    choose_.draw();
    drawButtons();
}

void PlayerSelect::switchAction() noexcept {}

void PlayerSelect::createButtons() noexcept
{
    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth / 2,
        data_->winHeight / 4,
        std::function<void(void)>([this](void) {
            if (this->data_->nbPlayer < 4) {
                data_->nbPlayer++;
                data_->players.emplace_back(std::make_unique<Player>(data_->nbPlayer - 1, data_));
            }
        }),
        1,
        "assets/fonts/menu.ttf",
        " Add",
        data_->winWidth / 2 + 100,
        data_->winHeight / 4 + 45);

    buttons_.emplace_back("assets/textures/home/button.png",
        1,
        data_->winWidth - data_->winWidth / 5,
        data_->winHeight - data_->winHeight / 4,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(SceneType::GAME)); }),
        1,
        "assets/fonts/menu.ttf",
        " Play game",
        data_->winWidth - (data_->winWidth / 5 + 50),
        data_->winHeight - 50);
}

void PlayerSelect::drawButtons() const noexcept
{
    for (auto it : buttons_) { it.draw(); }
}

void PlayerSelect::resetCameraman(Cameraman& camera) noexcept
{
    camera.tpTo(camera_position_, camera_target_, camera_up_);
}

void PlayerSelect::action([[maybe_unused]] Cameraman& camera, MouseHandler mouse_) noexcept
{
    for (auto& it : buttons_) {
        if (it.checkCollision(mouse_)) { it.action(); }
    }
}

void PlayerSelect::DestroyPool() noexcept {}

void PlayerSelect::CollisionPool() noexcept {}

void PlayerSelect::playMusic() const noexcept
{
    loop_music_.play();
}

MusicManager PlayerSelect::getMusicManager() const noexcept
{
    return (loop_music_);
}

Vector3 PlayerSelect::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 PlayerSelect::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 PlayerSelect::getCameraUp() const noexcept
{
    return (camera_up_);
}

void PlayerSelect::drawBackground() const noexcept
{
    background_.draw({ 255, 255, 255, 175 });
    title_.draw();
}

ColorManager PlayerSelect::getBackgroundColor() const noexcept
{
    return (background_color_);
}