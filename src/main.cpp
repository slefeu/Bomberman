#include <iostream>
#include <memory>

#include "Core.hpp"
#include "Error.hpp"
#include "Window.hpp"

int main()
{
    try {
        srand(time(NULL));

        auto data   = std::make_unique<GameData>(60, 1920, 1080, 2);
        auto window = std::make_unique<WindowManager>();
        auto core   = std::make_unique<Core>(data.get(), window.get());

        core->run();
        data.reset();
        core.reset();
        // window->close();
    } catch (const Error& error) {
        std::cerr << error.what() << std::endl;
        return (84);
    }
    return (0);
}
