/*
** EPITECH PROJECT, 2022
** YEP
** File description:
** PlayerSelect
*/

#include "PlayerSelect.hpp"

PlayerSelect::PlayerSelect(Core& core_ref) noexcept
    : Scene()
    , loop_music_(MUSIC)
    , core_entry_(core_ref)
    , background_color_(Colors::C_WHITE)
    , background_(BG_PATH, 0, 0, 1.1)
    , title_(TITLE_PATH, 30, 30)
    , choose_text_(SELECT, "Select players", 0, 0)
{
    choose_text_.setTextSize(40);
    choose_text_.setPosition(
        core_entry_.getWindow().getWidth() / 2, core_entry_.getWindow().getHeight() / 9);
    createButtons();
    stats_.emplace_back(
        "assets/textures/selection/normal.png", core_entry_.getWindow().getWidth() / 2, 50);
    stats_.emplace_back("assets/textures/selection/attack.png");
    stats_.emplace_back("assets/textures/selection/tactical.png");
    stats_.emplace_back("assets/textures/selection/runner.png");
    texts_.emplace_back("assets/fonts/menu.ttf", "Balanced", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Attack", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Tactical", 0, 0);
    texts_.emplace_back("assets/fonts/menu.ttf", "Runner", 0, 0);
}

void PlayerSelect::display3D() noexcept
{
    float nbPlayers = 0;
    for (auto& player : core_entry_.getData().getPlayers()) {
        auto render    = player->getComponent<Render>();
        auto transform = player->getComponent<Transform3D>();

        if (!render.has_value() || !transform.has_value()) continue;

        Vector3D position = { 0.2f, 0.6f, 4.5f - nbPlayers * 2 };
        Vector3D rotation = { 0, 1, 0 };

        render->get().setAnimationId(1);
        render->get().displayModelV(transform->get(), position, rotation, 180.0f);
        nbPlayers++;
    }
}

void PlayerSelect::display2D() noexcept
{
    FpsHandler::draw(10, 10);
    choose_text_.draw();
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
    int   height    = core_entry_.getWindow().getHeight();
    float nbPlayers = 0;

    for (auto& player : core_entry_.getData().getPlayers()) {
        Vector2 pos_l    = { 70 + 460 * nbPlayers, static_cast<float>(height - height / 7) + 40 };
        Vector2 pos_r    = { pos_l.x + 320, static_cast<float>(height - height / 7) + 40 };
        Vector2 position = { 120 + 460 * nbPlayers, 600 };
        displayPlayerStats(position,
            { pos_l.x + 85, pos_l.y + 25 },
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
    texts_[id].setPosition(texts_pos.x, texts_pos.y);
    texts_[id].draw();
}

void PlayerSelect::switchAction() noexcept
{
    core_entry_.getCameraman().tpTo(
        { 4.0f, 2.0f, 1.5f }, { 0.0f, 1.0f, 1.5f }, { 0.0f, 2.0f, 0.0f });
}

void PlayerSelect::createButtons() noexcept
{
    int width  = core_entry_.getWindow().getWidth();
    int height = core_entry_.getWindow().getHeight();

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 4 + 200,
        height / 6,
        std::function<void(void)>([this](void) {
            if (core_entry_.getData().getNbPlayers() < 4) {
                core_entry_.getData().setNbPlayers(core_entry_.getData().getNbPlayers() + 1);
                core_entry_.getData().addPlayer(core_entry_.getData().getNbPlayers() - 1);
                auto& new_player =
                    *reinterpret_cast<Player*>(core_entry_.getData().getPlayers().back().get());
                select_right_.emplace_back("assets/textures/selection/right.png",
                    0,
                    0,
                    std::function<void(void)>([&new_player](void) {
                        new_player.setPlayerType(
                            static_cast<PlayerType>(new_player.findNextType()));
                    }),
                    "assets/fonts/menu.ttf",
                    "",
                    0.2f);
                select_left_.emplace_back("assets/textures/selection/left.png",
                    0,
                    0,
                    std::function<void(void)>([&new_player](void) {
                        new_player.setPlayerType(
                            static_cast<PlayerType>(new_player.findPrevType()));
                    }),
                    "assets/fonts/menu.ttf",
                    "",
                    0.2f);
            }
        }),
        "assets/fonts/menu.ttf",
        "Add");

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 4 + 550,
        height / 6,
        std::function<void(void)>([this](void) {
            if (core_entry_.getData().getNbPlayers() > 2) {
                core_entry_.getData().setNbPlayers(core_entry_.getData().getNbPlayers() - 1);
                core_entry_.getData().getPlayers().pop_back();
                select_right_.pop_back();
                select_left_.pop_back();
            }
        }),
        "assets/fonts/menu.ttf",
        " Remove");

    buttons_.emplace_back("assets/textures/home/button.png",
        width / 4 + 900,
        height / 6,
        std::function<void(void)>([this](void) {
            if (this->core_entry_.getData().getNbPlayers() > 1)
                core_entry_.switchScene(bomberman::SceneType::GAME);
        }),
        "assets/fonts/menu.ttf",
        "Play");

    buttons_.emplace_back("assets/textures/selection/close.png",
        width / 4 + 1250,
        height / 6,
        std::function<void(void)>(
            [this](void) { core_entry_.switchScene(bomberman::SceneType::MENU); }),
        "assets/fonts/menu.ttf",
        "");
}

void PlayerSelect::drawButtons() const noexcept
{
    for (auto& it : buttons_) { it.draw(); }
}

void PlayerSelect::action() noexcept
{
    if (controller.isGamepadConnected(0)) {
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_UP))
            button_index_ = (button_index_ - 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_DOWN))
            button_index_ = (button_index_ + 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_B)) buttons_[button_index_].action();
        for (auto& it : buttons_) it.setState(0);
        buttons_[button_index_].setState(1);
    } else {
        for (auto& it : buttons_)
            if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    }
    for (auto& it : select_left_) {
        if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    }
    for (auto& it : select_right_) {
        if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    }
}

void PlayerSelect::DestroyPool() noexcept {}

void PlayerSelect::CollisionPool() noexcept {}

void PlayerSelect::playMusic() noexcept
{
    loop_music_.play();
}

void PlayerSelect::updateMusic() const noexcept
{
    loop_music_.update();
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