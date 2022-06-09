#include <iostream>
#include <memory>

#include "Core.hpp"
#include "Error.hpp"
#include "Window.hpp"

int main()
{
    try {
        srand(time(NULL));

        auto data   = std::make_unique<GameData>(60, 0, 0, 0);
        auto window = std::make_unique<WindowManager>();
        auto core   = std::make_unique<Core>(data.get(), window.get());

        core->run();
        data.reset();
        core.reset();
    } catch (const Error& error) {
        std::cerr << error.what() << std::endl;
        return (
            static_cast<typename std::underlying_type<ReturnCode>::type>(ReturnCode::ERROR_CODE));
    }
    return (static_cast<typename std::underlying_type<ReturnCode>::type>(ReturnCode::SUCCESS_CODE));
}
