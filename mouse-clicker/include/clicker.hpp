#pragma once

#include "mouse-button.hpp"
#include "mouse.hpp"

#include <chrono>
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

    [[nodiscard]] auto isRunning() const -> bool;

private:
    bool running{ false };
    unsigned int repeats{ 1 }; // 0 - repeats forever, > 0 - repeats n times
    unsigned int x{};
    unsigned int y{};
    Button button{ Button::LEFT };

    std::chrono::milliseconds interval{ 0 };
    std::jthread loopThread;
    std::binary_semaphore loopSemaphore{ 0 };

    Mouse& mouse;

    auto loop() -> void;
};

} // namespace mouse_clicker
