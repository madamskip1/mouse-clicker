#include "mouse-button.hpp"
#include "mouse.hpp"

#include <X11/Xlib.h>
#include <cassert>
#include <memory>
#include <print>

namespace mouse_clicker
{

class MouseLinux final : public Mouse
{
public:
    MouseLinux();
    ~MouseLinux();

    MouseLinux(const MouseLinux&) = delete;
    auto operator=(const MouseLinux&) -> MouseLinux& = delete;

    MouseLinux(MouseLinux&&) = delete;
    auto operator=(MouseLinux&&) -> MouseLinux& = delete;

    auto click(Button button, unsigned int x, unsigned int y) -> void final;

private:
    Display* display{ nullptr };

    auto moveCursor(unsigned int x, unsigned int y) -> void;
};

MouseLinux::MouseLinux()
    : display(XOpenDisplay(nullptr))
{
    assert(display != nullptr);
}

MouseLinux::~MouseLinux()
{
    if (display != nullptr)
    {
        XCloseDisplay(display);
    }
}


auto MouseLinux::click(Button button, unsigned int x, unsigned int y) -> void
{
    moveCursor(x, y);

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

auto MouseLinux::moveCursor(unsigned int x, unsigned int y) -> void
{
    const auto rootWindow = DefaultRootWindow(display);

    XWarpPointer(display, None, rootWindow, 0, 0, 0, 0, static_cast<int>(x), static_cast<int>(y));
    XFlush(display);
}

auto createMouse() -> std::unique_ptr<Mouse>
{
    return std::make_unique<MouseLinux>();
}

} // namespace mouse_clicker
