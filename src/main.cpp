#include <iostream>
#include <memory>

#include "Core.hpp"

int main(void)
{
    srand(time(NULL));

    std::unique_ptr<GameData> data = std::make_unique<GameData>(60, 1280, 720, 1);
    std::unique_ptr<Core>     core = std::make_unique<Core>(data.get());

    core->run();

    // Suppression des elements de la memoire (surtout des models 3D) avant la fermeture de la fenêtre
    data.reset();
    core.reset();

    CloseWindow();
    return 0;
}