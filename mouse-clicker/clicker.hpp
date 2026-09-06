#pragma once

namespace mouse_clicker
{
class Clicker
{
public:
    Clicker() = default;

    auto start() -> void;
    auto stop() -> void;

    [[nodiscard]] auto isRunning() const -> bool;

private:
    bool running{ false };
};

} // namespace mouse_clicker
