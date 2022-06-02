/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Home
*/

#include "Home.hpp"

#include "Shortcuts.hpp"

Home::Home(GameData* data, Core& core_ref) noexcept
    : Scene()
    , core_entry_(core_ref)
    , data_(data)
{
    loop_music_ = LoadMusicStream(MENU_MUSIC);

    // background attributes
    Image background = LoadImage("assets/textures/menu_background.png");
    Image title_bg   = LoadImage("assets/textures/menu_title.png");
    title            = LoadTextureFromImage(title_bg);
    texture          = LoadTextureFromImage(background);
    UnloadImage(background); // Unload image from RAM
    UnloadImage(title_bg);

    // button attributes
    buttons_.emplace_back("assets/textures/blankPage.png", 1, 300, 300);
}

Home::~Home() noexcept
{
    UnloadMusicStream(loop_music_);
    unloadTextures();
    unloadSounds();
}

void Home::resetCamera(Cameraman& camera) noexcept
{
    camera.moveTo(camera_position_, camera_target_, camera_up_);
}

void Home::display3D() noexcept {}

void Home::display2D() noexcept
{
    DrawFPS(10, 10);
    drawButtons();
}

void Home::action(Cameraman& camera, Vector2 mouse_pos) noexcept
{
    (void)camera;
    for (auto& it : buttons_) {
        if (it.checkCollision(mouse_pos)) {
            core_entry_.switchScene(SceneType::GAME);
        }
    }
}

void Home::DestroyPool() noexcept {}

void Home::CollisionPool() noexcept {}

Music Home::getLoopMusic() const noexcept
{
    return (loop_music_);
}

void Home::playMusic() const noexcept
{
    PlayMusicStream(loop_music_);
}

Vector3 Home::getCameraPosition() const noexcept
{
    return (camera_position_);
}

Vector3 Home::getCameraTarget() const noexcept
{
    return (camera_target_);
}

Vector3 Home::getCameraUp() const noexcept
{
    return (camera_up_);
}

Color Home::getBackgroundColor() const noexcept
{
    return (background_color_);
}

void Home::setButtons() noexcept
{
    for (auto& it : buttons_) { it.setButtonAction(false); }
}

void Home::unloadTextures() noexcept
{
    UnloadTexture(texture); // Texture unloading
}

void Home::unloadSounds() noexcept
{
    for (auto it : buttons_) { it.unload(); }
}

void Home::drawBackground() const noexcept
{
    Vector2 position = { 0, -45 };
    DrawTextureEx(
        texture, position, 0, 1, CLITERAL(Color){ 255, 255, 255, 175 });
    DrawTexture(title, 30, 30, WHITE);
}

void Home::drawButtons() const noexcept
{
    for (auto it : buttons_) { it.draw(); }
}