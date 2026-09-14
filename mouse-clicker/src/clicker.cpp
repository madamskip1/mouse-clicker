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
    loopSemaphore.release();
}

auto Clicker::start() -> void
{
    assert(!running);

    loopSemaphore.try_acquire();
    running = true;

    loopThread = std::jthread(&Clicker::loop, this);

    if (onStartCallback)
    {
        onStartCallback();
    }
}

auto Clicker::stop() -> void
{
    assert(running);

    running = false;
    loopSemaphore.release();
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

auto Clicker::setOnStartCallback(std::function<void()> callback) -> void
{
    onStartCallback = std::move(callback);
}

auto Clicker::setOnStopCallback(std::function<void()> callback) -> void
{
    onStopCallback = std::move(callback);
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

        if (interval.count() > 0)
        {
            loopSemaphore.try_acquire_for(interval);
        }
    }
    running = false;

    if (onStopCallback)
    {
        onStopCallback();
    }
}

} // namespace mouse_clicker
