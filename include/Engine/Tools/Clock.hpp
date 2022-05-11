/*
** EPITECH PROJECT, 2022
** B-YEP-400-BDX-4-1-indiestudio-arthur.decaen
** File description:
** Clock
*/

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

class Clock
{
  private:
    float lifeTime;
    float currentTime;

  public:
    Clock(float lifeTime) noexcept;
    ~Clock() noexcept = default;
    void updateClock(void) noexcept;
    bool clockDone(void) noexcept;
};

#endif /* !CLOCK_HPP_ */
