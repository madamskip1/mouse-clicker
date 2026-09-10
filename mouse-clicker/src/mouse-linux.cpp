#include "mouse-linux.hpp"

#include <print>

namespace mouse_clicker
{

auto MouseLinux::click(Button button, unsigned int x, unsigned int y) -> void
{
    auto mouseButtonToString = [](Button button) -> std::string {
        using enum mouse_clicker::Button;

        switch (button)
        {
        case LEFT:
            return "left";
        case MIDDLE:
            return "middle";
        case RIGHT:
            return "right";
        default:
            return "unknown";
        }
    };

    std::println("Clicking {} at ({}, {})", mouseButtonToString(button), x, y);
}

} // namespace mouse_clicker
