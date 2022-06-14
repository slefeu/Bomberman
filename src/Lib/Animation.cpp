/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Animation
*/

#include "Animation.hpp"

#include <stdlib.h>
#include <iostream>
#include "DeltaTime.hpp"

/**
 * If there are animations, unload them and free the memory.
 *
 * @return A pointer to the first element of the array.
 */
Animation::~Animation() noexcept
{
    if (!animations_) return;
    for (unsigned int i = 0; i < animations_count_; i++) UnloadModelAnimation(animations_[i]);
    RL_FREE(animations_);
}

/**
 * It loads the animations from the file path and stores them in the animations_ array
 *
 * @param path The path to the model file.
 */
void Animation::addAnimation(const std::string_view& path) noexcept
{
    animations_  = LoadModelAnimations(path.data(), &animations_count_);
    is_animated_ = true;
}

/**
 * It updates the animation of the model
 *
 * @param model_ The model to update.
 *
 * @return A reference to the animation object.
 */
void Animation::updateAnimation(Model3D& model_) noexcept
{
    time_ += DeltaTime::getDeltaTime();
    std::cout << "time\n" <<  time_ << std::endl;
    if (animations_ == nullptr) return;
    if (is_animated_ == false) return;
    if (time_ < 0.01) return;
    time_ = 0;
    frame_counter_ += 1.0f * skip_frame_;
    model_.update(animations_[animation_id_], frame_counter_);
    if (frame_counter_ >= animations_[animation_id_].frameCount) frame_counter_ = 0;
}

/**
 * Sets the number of frames to skip.
 *
 * @param frame The frame to skip to.
 */
void Animation::setSkipFrame(int frame) noexcept
{
    skip_frame_ = frame;
}

/**
 * Sets the animation id.
 *
 * @param id The id of the animation.
 */
void Animation::setAnimationId(int id) noexcept
{
    animation_id_ = id;
}