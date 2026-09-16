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

class MouseLinuxX11 final : public Mouse
{
public:
    MouseLinuxX11();
    ~MouseLinuxX11();

    MouseLinuxX11(const MouseLinuxX11&) = delete;
    auto operator=(const MouseLinuxX11&) -> MouseLinuxX11& = delete;

    MouseLinuxX11(MouseLinuxX11&&) = delete;
    auto operator=(MouseLinuxX11&&) -> MouseLinuxX11& = delete;

    auto click(Button button, unsigned int x, unsigned int y) -> void final;

private:
    Display* display{ nullptr };

    auto moveCursor(unsigned int x, unsigned int y) -> void;
};

MouseLinuxX11::MouseLinuxX11()
    : display(XOpenDisplay(nullptr))
{
    assert(display != nullptr);
}

MouseLinuxX11::~MouseLinuxX11()
{
    if (display != nullptr)
    {
        XCloseDisplay(display);
    }
}


auto MouseLinuxX11::click(Button button, unsigned int x, unsigned int y) -> void
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

    moveCursor(x, y);

    XTestFakeButtonEvent(display, x11Button, True, CurrentTime);  // press
    XTestFakeButtonEvent(display, x11Button, False, CurrentTime); // release
}

auto MouseLinuxX11::moveCursor(unsigned int x, unsigned int y) -> void
{
    const auto rootWindow = DefaultRootWindow(display);

    XWarpPointer(display, None, rootWindow, 0, 0, 0, 0, static_cast<int>(x), static_cast<int>(y));
    XFlush(display);
}

auto createMouse() -> std::unique_ptr<Mouse>
{
    return std::make_unique<MouseLinuxX11>();
}

} // namespace mouse_clicker
