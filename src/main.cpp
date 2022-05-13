#include <iostream>

#include "Core.hpp"

int main(void)
{
    srand(time(NULL));

    Settings settings(60, 1280, 720, 1);
    Core     core(&settings);
    core.run();
    return 0;
}