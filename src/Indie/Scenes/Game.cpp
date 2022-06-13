/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Game
*/

#include "Game.hpp"

#include <iostream>

#include "Crate.hpp"
#include "DeltaTime.hpp"
#include "InstanceOf.hpp"
#include "Item.hpp"
#include "MyCameraman.hpp"
#include "Player.hpp"
#include "Round.hpp"
#include "Wall.hpp"

Game::Game(Core& core_ref) noexcept
    : Scene()
    , core_entry_(core_ref)
    , chrono_(time_party_)
    , isHurry(false)
    , nbBlockPlaced(0)
    , loop_music_(GAME_MUSIC)
    , hurry_music_(HURRY_MUSIC)
    , victory_music_(VICTORY_MUSIC)
    , background_color_(Colors::C_BLACK)
    , startSound_(START)
    , hurryUpSound_(HURRY_UP)
    , victoryText_("assets/fonts/menu.ttf", "", 0, 30)
    , hurryUpText_(
          "assets/fonts/menu.ttf", "Hurry Up !", 0, core_entry_.getWindow().getHeight() / 2 - 80)
    , timeText_("assets/fonts/menu.ttf", "Timer", 0, 10)
    , pauseText_("assets/fonts/menu.ttf",
          "Pause",
          core_entry_.getWindow().getWidth() / 2 - 220,
          core_entry_.getWindow().getHeight() / 2 - 80)
{
    hurryUpSound_.setVolume(0.7f);
    createButtons();
    hurryUpText_.setTextSize(100);
    hurryUpText_.setTextColor(Colors::C_RED);

    victoryText_.setTextSize(100);
    victoryText_.setTextColor(Colors::C_GOLD);

    pauseText_.setTextSize(100);
    pauseText_.setTextColor(Colors::C_RED);
}

void Game::switchAction() noexcept
{
    core_entry_.getCameraman().tpTo(
        { 0.0f, 1.0f, 2.0f }, { 0.0f, 1.0f, 0.0f }, { 0.0f, 2.0f, 0.0f });
    core_entry_.getCameraman().moveTo(camera_position_, camera_target_, camera_up_);

    for (auto& player : core_entry_.getData().getPlayers()) {
        if (!Type:: instanceof <Player>(player.get())) continue;
        auto type = ((std::unique_ptr<Player>&)player)->getPlayerType();
        ((std::unique_ptr<Player>&)player)->setPlayerType(type);
        ((std::unique_ptr<Player>&)player)->setPosition();
        ((std::unique_ptr<Player>&)player)->setWallPass(false);
        ((std::unique_ptr<Player>&)player)->getComponent<Render>()->get().setColor(Colors::C_WHITE);

        auto render = player->getComponent<Render>();
        if (render.has_value()) { render->get().show(true); }
    }

    chrono_.resetTimer();
    loop_music_.play();
    hurry_music_.stop();
    startSound_.play();
    core_entry_.getData().clearEntities();
    createMap();
    srand(time(NULL));

    isHurry       = false;
    nbBlockPlaced = 0;
    x             = -6;
    z             = 7;
    maxX          = 6;
    maxZ          = 6;
    minX          = -5;
    minZ          = -4;
    direction     = Direction::UP;

    end_game = false;
    pause    = false;

    for (auto& text : playerText_) { text.unload(); }
    playerText_.clear();

    int width   = core_entry_.getWindow().getWidth();
    int height  = core_entry_.getWindow().getHeight();
    int xPos[4] = { 70, width - 150, width - 150, 70 };
    int yPos[4] = { 30, height - 80, 30, height - 80 };
    for (int i = 0; i < 4; i++) {
        playerText_.emplace_back("assets/fonts/menu.ttf", "Stats", xPos[i], yPos[i]);
    }
    for (auto& text : playerText_) { text.setTextSize(20); }
}

void Game::playMusic() noexcept
{
    loop_music_.play();
}

void Game::updateMusic() const noexcept
{
    if (loop_music_.isPlaying()) loop_music_.update();
    else if (hurry_music_.isPlaying())
        hurry_music_.update();
    else
        victory_music_.update();
}

void Game::action() noexcept
{
    SystemDestroy();
    SystemCollision();

    if (pause) {
        pauseAction();
        return;
    }
    for (auto& player : core_entry_.getData().getPlayers()) player->Update();
    if (!end_game) {
        int alive = 0;
        for (auto& player : core_entry_.getData().getPlayers()) {
            if (!Type:: instanceof <Player>(player.get())) continue;

            auto render = player->getComponent<Render>();
            if (render.has_value() && render->get().isShow()) alive++;
        }
        if (alive == 1 || alive == 0 || chrono_.isTimerDone()) { endGame(); }
    } else {
        endGameAction();
        return;
    }

    chrono_.updateTimer();
    for (auto& entity : core_entry_.getData().getEntities()) entity->Update();

    if (!core_entry_.getCameraman().getIsMoving())
        core_entry_.getCameraman().lookBetweenEntity(core_entry_.getData().getPlayers());

    // Activation du Hurry Up !
    if (int(round(chrono_.getTime())) <= 55 && !isHurry) {
        isHurry            = true;
        lastTimeBlockPlace = chrono_.getTime();
        HurryUpX           = core_entry_.getWindow().getWidth() - 100;
        hurryUpSound_.play();
        hurry_music_.play();
        loop_music_.stop();
    }
    hurryUp();

    int xPos[4] = {
        25, core_entry_.getWindow().getWidth() - 50, core_entry_.getWindow().getWidth() - 50, 25
    };
    int yPos[4] = {
        10, core_entry_.getWindow().getHeight() - 100, 10, core_entry_.getWindow().getHeight() - 100
    };
    auto& sprites = core_entry_.getData().getSprites();
    for (size_t i = 0; i != core_entry_.getData().getPlayers().size(); i++)
        sprites[i]->setPos(xPos[i], yPos[i]);

    if ((controller.isGamepadConnected(0) && controller.isGamepadButtonPressed(0, G_Button::G_Y))
        || controller.isKeyPressed(Key::K_ENTER))
        pause = true;
}

void Game::createMap() noexcept
{
    Vector3D vectorTemp;

    // Ajout des murs autour de la carte
    for (int z = -5; z < 8; z++)
        for (int x = -7; x < 8; x++)
            if (x == -7 || x == 7 || z == -5 || z == 7) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                core_entry_.getData().addWall(vectorTemp);
            }

    // Ajout des murs une case sur deux
    for (int z = -4; z < 6; z++)
        for (int x = -5; x < 6; x++)
            if (x % 2 != 0 && z % 2 != 0) {
                vectorTemp = { x * 1.0f, 0.0f, z * 1.0f };
                core_entry_.getData().addWall(vectorTemp);
            }

    // Génération des boites
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if ((x == -6 && z == -4) || (x == 6 && z == -4) || (x == -6 && z == 6)
                || (x == 6 && z == 6) || (x == -6 && z == -3) || (x == 6 && z == -3)
                || (x == -6 && z == 5) || (x == 6 && z == 5) || (x == -5 && z == -4)
                || (x == 5 && z == -4) || (x == -5 && z == 6) || (x == 5 && z == 6))
                continue;

            Vector3D vectorTemp = { x * 1.0f, 0.01f, z * 1.0f };

            bool spawnCrate = true;
            for (auto& entity : core_entry_.getData().getEntities()) {
                auto transform = entity->getComponent<Transform3D>();
                if (transform == std::nullopt) continue;

                Vector3D pos = transform->get().getPosition();
                if (pos.x == vectorTemp.x && pos.z == vectorTemp.z) {
                    spawnCrate = false;
                    break;
                }
            }
            if (rand() % 100 < 80 && spawnCrate) core_entry_.getData().addCrate(vectorTemp);
        }
}

void Game::hurryUp() noexcept
{
    if (!isHurry) return;
    float time = chrono_.getTime();
    if (lastTimeBlockPlace - time >= 0.37f) {
        Vector3D vectorTemp;
        if (direction == Direction::UP) {
            z--;
            if (z == minZ) {
                direction = Direction::RIGHT;
                minZ++;
                x--;
            }
        }
        if (direction == Direction::RIGHT) {
            x++;
            if (x == maxX) {
                direction = Direction::DOWN;
                maxX--;
                z--;
            }
        }
        if (direction == Direction::DOWN) {
            z++;
            if (z == maxZ) {
                direction = Direction::LEFT;
                maxZ--;
                x++;
            }
        }
        if (direction == Direction::LEFT) {
            x--;
            if (x == minX) {
                direction = Direction::UP;
                minX++;
            }
        }
        vectorTemp = { x * 1.0f, 5.0f, z * 1.0f };
        core_entry_.getData().addWall(vectorTemp);
        lastTimeBlockPlace = chrono_.getTime();
        nbBlockPlaced++;
    }
    HurryUpX -= 500.0f * DeltaTime::getDeltaTime();
    if (nbBlockPlaced >= 80 && isHurry) isHurry = false;
}

ColorManager Game::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void Game::endGame() noexcept
{
    end_game = true;

    loop_music_.stop();
    hurry_music_.stop();
    victory_music_.play();

    core_entry_.getCameraman().lookBetweenEntity(core_entry_.getData().getPlayers());

    auto pos    = core_entry_.getCameraman().getPosition();
    auto target = core_entry_.getCameraman().getTarget();
    auto up     = core_entry_.getCameraman().getUp();

    int nbAlive = 0;
    int index   = 0;
    for (size_t i = 0; i < core_entry_.getData().getPlayers().size(); i++) {
        auto trans  = core_entry_.getData().getPlayers()[i]->getComponent<Transform3D>();
        auto render = core_entry_.getData().getPlayers()[i]->getComponent<Render>();

        if (!trans.has_value() || !render.has_value()) continue;

        render->get().getAnimation().setAnimationId(3);
        trans->get().setRotationAngle(90.0f);

        if (render->get().isShow()) {
            nbAlive++;
            index = i;
        }
    }

    if (nbAlive == 1) {
        victoryText_.setText("Player " + std::to_string(index + 1) + " win !");
        victoryText_.setPosition(core_entry_.getWindow().getWidth() / 2 - 480, 30);
        auto transform = core_entry_.getData().getPlayers()[index]->getComponent<Transform3D>();

        if (transform.has_value()) {
            pos    = transform->get().getPosition();
            target = pos;
            target.z -= 1.0f;
            core_entry_.getCameraman().tpTo({ pos.x, 20.0f, pos.z + 3.0f }, target, up);
            core_entry_.getCameraman().moveTo({ pos.x, 5.0f, pos.z + 3.0f }, target, up);
        }
    } else {
        victoryText_.setText("Draw !");
        victoryText_.setPosition(core_entry_.getWindow().getWidth() / 2 - 200, 30);
        core_entry_.getCameraman().tpTo(pos, target, up);
    }
}

void Game::endGameAction() noexcept
{
    if (controller.isGamepadConnected(0)) {
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_LEFT))
            button_index_ = (button_index_ - 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_DPAD_RIGHT))
            button_index_ = (button_index_ + 1) % buttons_.size();
        if (controller.isGamepadButtonPressed(0, G_Button::G_B)) buttons_[button_index_].action();
        for (auto& it : buttons_) it.setState(0);
        buttons_[button_index_].setState(1);
    } else {
        for (auto& it : buttons_)
            if (it.checkCollision(core_entry_.getData().getMouseHandler())) { it.action(); }
    }
}

void Game::endGameDisplay() noexcept
{
    for (auto& it : buttons_) { it.draw(); }
    victoryText_.draw();
}

void Game::createButtons() noexcept
{
    int width  = core_entry_.getWindow().getWidth();
    int height = core_entry_.getWindow().getHeight();

    buttons_.emplace_back("assets/textures/home/button.png",
        50,
        height - 200,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(bomberman::SceneType::GAME)); }),
        "assets/fonts/menu.ttf",
        "Restart");

    buttons_.emplace_back("assets/textures/home/button.png",
        width - 350,
        height - 200,
        std::function<void(void)>(
            [this](void) { return (core_entry_.switchScene(bomberman::SceneType::MENU)); }),
        "assets/fonts/menu.ttf",
        "Menu");
}

void Game::pauseAction() noexcept
{
    if ((controller.isGamepadConnected(0) && controller.isGamepadButtonPressed(0, G_Button::G_Y))
        || controller.isKeyPressed(Key::K_ENTER))
        pause = false;
}

// ****************************************************************************
// *                               SYSTEMS                                    *
// ****************************************************************************

void Game::SystemDestroy() noexcept
{
    size_t len = core_entry_.getData().getEntities().size();
    for (size_t i = 0; i != len; i++) {
        if (!core_entry_.getData().getEntities()[i]->getEnabledValue()) {
            core_entry_.getData().getEntities().erase(
                core_entry_.getData().getEntities().begin() + i);
            len--;
            i--;
        }
    }
}

void Game::SystemCollision() noexcept
{
    for (auto& player : core_entry_.getData().getPlayers()) {
        for (auto& entity : core_entry_.getData().getEntities()) {
            auto hitbox       = player->getComponent<BoxCollider>();
            auto other_hitbox = entity->getComponent<BoxCollider>();
            if (hitbox == std::nullopt || other_hitbox == std::nullopt) continue;
            if (hitbox->get().isColliding(other_hitbox->get())) {
                player->OnCollisionEnter(entity);
                entity->OnCollisionEnter(player);
            }
        }
    }
    for (auto& entity1 : core_entry_.getData().getEntities()) {
        for (auto& entity : core_entry_.getData().getEntities()) {
            auto hitbox       = entity1->getComponent<BoxCollider>();
            auto other_hitbox = entity->getComponent<BoxCollider>();
            if (hitbox == std::nullopt || other_hitbox == std::nullopt) continue;
            if (!hitbox->get().getIsSolid() || !other_hitbox->get().getIsSolid()) continue;
            if (entity1 == entity) continue;
            if (hitbox->get().isColliding(other_hitbox->get())) {
                entity1->OnCollisionEnter(entity);
                entity->OnCollisionEnter(entity1);
            }
        }
    }
}

void Game::SystemDisplay() noexcept
{
    // **************************** 3D **********************************

    core_entry_.getCameraman().begin3D();

    DrawPlane({ 0.0f, 0.0f, 1.0f }, { 13.0f, 11.0f }, { 0, 207, 68, 255 });
    for (int z = -4; z < 7; z++)
        for (int x = -6; x < 7; x++) {
            if (z % 2 == 0 && x % 2 == 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
            if (z % 2 != 0 && x % 2 != 0)
                DrawPlane({ x * 1.0f, 0.01f, z * 1.0f }, { 1.0f, 1.0f }, { 0, 181, 48, 255 });
        }

    for (auto& player : core_entry_.getData().getPlayers()) {
        auto transform = player->getComponent<Transform3D>();
        auto renderer  = player->getComponent<Render>();
        if (!transform.has_value() || !renderer.has_value()) continue;
        if (!player->getEnabledValue()) continue;
        renderer->get().display(transform->get());
    }
    for (auto& entity : core_entry_.getData().getEntities()) {
        auto transform = entity->getComponent<Transform3D>();
        auto renderer  = entity->getComponent<Render>();
        if (!transform.has_value() || !renderer.has_value()) continue;
        if (!entity->getEnabledValue()) continue;
        renderer->get().display(transform->get());
    }

    core_entry_.getCameraman().end3D();

    // **************************** 2D **********************************

    FpsHandler::draw(35, 70);

    if (end_game) {
        endGameDisplay();
        return;
    }
    if (pause) { pauseText_.draw(); }

    if (!chrono_.isTimerDone()) {
        auto time = std::to_string(int(round(chrono_.getTime())));
        timeText_.setText(time);
        timeText_.setPosition(core_entry_.getWindow().getWidth() / 2 - (time.size() * 2), 10);
        timeText_.draw();
    }

    if (isHurry) {
        hurryUpText_.setPosition(HurryUpX, core_entry_.getWindow().getHeight() / 2 - 60);
        hurryUpText_.draw();
    }

    auto& sprites = core_entry_.getData().getSprites();
    for (size_t i = 0; i != core_entry_.getData().getNbPlayers(); i++) {
        sprites[i]->draw();
        auto player = (&(std::unique_ptr<Player>&)(core_entry_.getData().getPlayers()[i]))->get();

        std::string speed = std::to_string(player->getSpeed());
        speed             = speed.substr(0, speed.find(".") + 2);
        playerText_[i].setText(std::to_string(player->getNbBomb()) + ", "
                               + std::to_string(player->getBombSize()) + ", " + speed);
        playerText_[i].draw();
    }
}