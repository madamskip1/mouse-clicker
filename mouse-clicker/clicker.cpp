#include "clicker.hpp"

#include <cassert>

namespace mouse_clicker
{

Clicker::Clicker(Mouse& mouse)
    : mouse(mouse)
{
}

auto Clicker::start() -> void
{
    assert(!running);

    running = true;

    loop(); // TODO: make it in separate thread
}

auto Clicker::stop() -> void
{
    assert(running);

    running = false;
}

auto Clicker::setRepeats(unsigned int repeats) -> void
{
    assert(!running);

    this->repeats = repeats;
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
        mouse.click(0, 0);
        ++repeat;
    }
    running = false;
}

} // namespace mouse_clicker
