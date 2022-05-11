#include <iostream>

#include "Core.hpp"

int main(void)
{
    srand(time(NULL));
    Core core(800, 600, 60);
    core.run();
    return 0;
}