#include "clicker.hpp"

#include <cassert>

namespace mouse_clicker
{

auto Clicker::start() -> void
{
    assert(!running);
    running = true;
}

auto Clicker::stop() -> void
{
    assert(running);
    running = false;
}

auto Clicker::isRunning() const -> bool
{
    return running;
}

} // namespace mouse_clicker
