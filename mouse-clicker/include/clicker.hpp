#pragma once

#include "mouse-button.hpp"
#include "mouse.hpp"

#include <chrono>
#include <functional>
#include <semaphore>
#include <thread>


namespace mouse_clicker
{

class Clicker
{
public:
    explicit Clicker(Mouse& mouse);
    ~Clicker();

    Clicker(const Clicker&) = delete;
    auto operator=(const Clicker&) -> Clicker& = delete;

    Clicker(Clicker&&) = delete;
    auto operator=(Clicker&&) -> Clicker& = delete;

    auto start() -> void;
    auto stop() -> void;

    auto setButton(Button button) -> void;
    auto setRepeats(unsigned int repeats) -> void;
    auto setCoords(unsigned int x, unsigned int y) -> void;

    template <typename Rep, typename Period>
    void setInterval(std::chrono::duration<Rep, Period> duration)
    {
        interval = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    }

    auto setOnStartCallback(std::function<void()> callback) -> void;
    auto setOnStopCallback(std::function<void()> callback) -> void;

    [[nodiscard]] auto isRunning() const -> bool;

private:
    std::function<void()> onStartCallback;
    std::function<void()> onStopCallback;

    std::jthread loopThread;

    std::binary_semaphore loopSemaphore{ 0 };

    std::chrono::milliseconds interval;
    unsigned int repeats;
    unsigned int x;
    unsigned int y;

    Button button;
    bool running;

    Mouse& mouse;

    auto loop() -> void;
};

} // namespace mouse_clicker
