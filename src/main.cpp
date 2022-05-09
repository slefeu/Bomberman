#include <iostream>

#include "Core.hpp"

int main(void)
{
    Core core(800, 600);
    core.setFPS(60);
    core.run();
    return 0;
}