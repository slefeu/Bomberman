#include <iostream>

#include "Core.hpp"

int main(void)
{
    srand(time(NULL));
    Core core(1280, 720, 60);
    core.run();
    return 0;
}