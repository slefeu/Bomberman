#include "DeltaTime.hpp"

#include "raylib.h"

float DeltaTime::getDeltaTime() noexcept
{
    return GetFrameTime();
}