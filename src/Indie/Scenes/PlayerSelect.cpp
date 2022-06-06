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
    , choose_(SELECT, "Select players", data_->winWidth / 2, data_->winHeight / 7)
{
    choose_.setTextColor(Colors::C_BLACK);
    choose_.setTextSize(40);
    createButtons();
    stats_.emplace_back("assets/textures/selection/normal.png", data_->winWidth / 2, 50);
    stats_.emplace_back("assets/textures/selection/attack.png");
    stats_.emplace_back("assets/textures/selection/tactical.png");
    stats_.emplace_back("assets/textures/selection/runner.png");
    texts_.emplace_back("assets/fonts/menu.ttf", "Balanced", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Attack", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Tactical", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Runner", 0, 0);
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
        Vector3 position = { 0.2f, 0.6f, 5 - nbPlayers * 2 };
        player->displayModel(position);
        nbPlayers++;
    }
}

void PlayerSelect::display2D() noexcept
{
    FpsHandler::draw(10, 10);
    choose_.draw();
    drawButtons();
    displayAllStats();
}

void PlayerSelect::drawSelection(
    const int id, const Vector2& pos_left, const Vector2& pos_right) noexcept
{
    select_left_[id].setPosition(pos_left);
    select_left_[id].draw();
    select_right_[id].setPosition(pos_right);
    select_right_[id].draw();
}

void PlayerSelect::displayAllStats() noexcept
{
    float nbPlayers = 0;
    for (auto& player : data_->players) {
        Vector2 pos_l    = { 10 + 460 * nbPlayers,
            static_cast<float>(data_->winHeight - data_->winHeight / 7) };
        Vector2 pos_r    = { pos_l.x + 300,
            static_cast<float>(data_->winHeight - data_->winHeight / 7) };
        Vector2 position = { 50 + 460 * nbPlayers, 600 };
        displayPlayerStats(position,
            { pos_l.x + 70, pos_l.y + 25 },
            findStatsId(((std::unique_ptr<Player>&)player)->getType()));
        drawSelection(static_cast<int>(nbPlayers), pos_l, pos_r);
        nbPlayers++;
    }
}

unsigned int PlayerSelect::findStatsId(const PlayerType& type) const noexcept
{
    if (type == PlayerType::NORMAL) { return (0); };
    if (type == PlayerType::ATTACK) { return (1); };
    if (type == PlayerType::TACTICAL) { return (2); };
    if (type == PlayerType::RUNNER) { return (3); };
    return (0);
}

void PlayerSelect::displayPlayerStats(
    const Vector2& stats_pos, const Vector2& texts_pos, int id) noexcept
{
    stats_[id].setPos(stats_pos.x, stats_pos.y);
    stats_[id].draw();
    texts_[id].setPos(texts_pos.x, texts_pos.y);
    texts_[id].draw();
}

void PlayerSelect::switchAction() noexcept {}

void PlayerSelect::createButtons() noexcept
{
    buttons_.emplace_back("assets/textures/home/button.png",
        data_->winWidth / 3 + 100,
        data_->winHeight / 5,
        std::function<void(void)>([this](void) {
            if (this->data_->nbPlayer < 4) {
                data_->nbPlayer++;
                data_->players.emplace_back(std::make_unique<Player>(data_->nbPlayer - 1, data_));
                auto& new_player = *reinterpret_cast<Player*>(data_->players.back().get());
                select_right_.emplace_back("assets/textures/selection/right.png",
                    0,
                    0,
                    std::function<void(void)>([&new_player](void) {
                        new_player.setPlayerType(
                            static_cast<PlayerType>(new_player.findNextType()));
                    }),
                    0.2f,
                    "assets/fonts/menu.ttf",
                    "",
                    0,
                    0);
                select_left_.emplace_back("assets/textures/selection/left.png",
                    0,
                    0,
                    std::function<void(void)>([&new_player](void) {
                        new_player.setPlayerType(
                            static_cast<PlayerType>(new_player.findPrevType()));
                    }),
                    0.2f,
                    "assets/fonts/menu.ttf",
                    "",
                    0,
                    0);
            }
        }),
        1,
        "assets/fonts/menu.ttf",
        " Add",
        data_->winWidth / 3 + 200,
        data_->winHeight / 5 + 45);

    buttons_.emplace_back("assets/textures/home/button.png",
        data_->winWidth / 3 + 450,
        data_->winHeight / 5,
        std::function<void(void)>([this](void) {
            if (this->data_->nbPlayer > 1) {
                data_->nbPlayer--;
                data_->players.pop_back();
                select_right_.pop_back();
                select_left_.pop_back();
                texts_.pop_back();
            }
        }),
        1,
        "assets/fonts/menu.ttf",
        " Remove",
        data_->winWidth / 3 + 500,
        data_->winHeight / 5 + 45);

    buttons_.emplace_back("assets/textures/home/button.png",
        data_->winWidth / 3 + 800,
        data_->winHeight / 5,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(SceneType::GAME)); }),
        1,
        "assets/fonts/menu.ttf",
        "Play",
        data_->winWidth / 3 + 900,
        data_->winHeight / 5 + 45);
}

void PlayerSelect::drawButtons() const noexcept
{
    for (auto& it : buttons_) { it.draw(); }
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
    for (auto& it : select_left_) {
        if (it.checkCollision(mouse_)) { it.action(); }
    }
    for (auto& it : select_right_) {
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