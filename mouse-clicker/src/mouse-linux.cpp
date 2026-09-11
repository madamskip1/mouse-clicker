#include "mouse-button.hpp"
#include "mouse.hpp"

#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <cassert>
#include <memory>
#include <print>
#include <string>

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
    unsigned int x11Button{};
    std::string buttonString;

    using enum mouse_clicker::Button;
    switch (button)
    {
    case LEFT:
        x11Button = Button1;
        buttonString = "left";
        break;
    case MIDDLE:
        x11Button = Button2;
        buttonString = "middle";
        break;
    case RIGHT:
        x11Button = Button3;
        buttonString = "right";
        break;
    default:
        assert(false);
    }

    // For now move and click are disabled
    // for easier development
    // Remove comments to enable

    // moveCursor(x, y);

    // XTestFakeButtonEvent(display, x11Button, True, CurrentTime); // press
    // XTestFakeButtonEvent(display, x11Button, False, CurrentTime); // release

    std::println("Clicking {} at ({}, {})", buttonString, x, y);
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
