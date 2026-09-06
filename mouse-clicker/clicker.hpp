#pragma once

#include "mouse.hpp"

namespace mouse_clicker
{
class Clicker
{
public:
    explicit Clicker(Mouse& mouse);
    ~Clicker() = default;

    Clicker(const Clicker&) = delete;
    auto operator=(const Clicker&) -> Clicker& = delete;

    Clicker(Clicker&&) = delete;
    auto operator=(Clicker&&) -> Clicker& = delete;

    auto start() -> void;
    auto stop() -> void;

    auto setRepeats(unsigned int repeats) -> void;
    auto setCoords(unsigned int x, unsigned int y) -> void;

    [[nodiscard]] auto isRunning() const -> bool;

private:
    bool running{ false };
    unsigned int repeats{ 1 }; // 0 - repeats forever, > 0 - repeats n times
    unsigned int x{};
    unsigned int y{};

    Mouse& mouse;

    auto loop() -> void;
};

} // namespace mouse_clicker
