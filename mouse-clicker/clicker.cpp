#include "clicker.hpp"

#include <cassert>

namespace mouse_clicker
{

Clicker::Clicker(Mouse& mouse)
    : mouse(mouse)
{
}

Clicker::~Clicker()
{
    running = false;

    if (loopThread.joinable())
    {
        loopThread.join();
    }
}

auto Clicker::start() -> void
{
    assert(!running);

    running = true;

    loopThread = std::thread(&Clicker::loop, this);
}

auto Clicker::stop() -> void
{
    assert(running);

    running = false;
    loopThread.join();
}

auto Clicker::setButton(Button button) -> void
{
    assert(!running);

    this->button = button;
}

auto Clicker::setRepeats(unsigned int repeats) -> void
{
    assert(!running);

    this->repeats = repeats;
}

auto Clicker::setCoords(unsigned int x, unsigned int y) -> void
{
    assert(!running);

    this->x = x;
    this->y = y;
}

auto Clicker::isRunning() const -> bool
{
    return running;
}

auto Clicker::loop() -> void
{
    unsigned int repeat = 0;

    while (running && (repeats == 0 /* forever */ || repeat < repeats))
    {
        mouse.click(button, x, y);
        ++repeat;
    }
    running = false;
}

} // namespace mouse_clicker
