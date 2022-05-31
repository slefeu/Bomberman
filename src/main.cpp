#include <iostream>
#include <memory>

#include "Core.hpp"
#include "Error.hpp"

int main(void)
{
    try {
        srand(time(NULL));

        std::unique_ptr<GameData> data =
            std::make_unique<GameData>(60, 1280, 720, 1);
        std::unique_ptr<Core> core = std::make_unique<Core>(data.get());
        core->run();
        data.reset();
        core.reset();
        CloseWindow();
    } catch (const Error& error) {
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}
