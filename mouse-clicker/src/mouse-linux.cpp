#include "mouse-button.hpp"
#include "mouse.hpp"

#include <memory>
#include <print>

namespace mouse_clicker
{


class MouseLinux final : public Mouse
{
public:
    MouseLinux() = default;

    auto click(Button button, unsigned int x, unsigned int y) -> void final;
};


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

auto createMouse() -> std::unique_ptr<Mouse>
{
    return std::make_unique<MouseLinux>();
}

} // namespace mouse_clicker
