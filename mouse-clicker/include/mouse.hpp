#pragma once

#include "mouse-button.hpp"

#include <memory>

namespace mouse_clicker
{

class Mouse
{
public:
    Mouse() = default;
    virtual ~Mouse() = default;

    Mouse(const Mouse&) = delete;
    auto operator=(const Mouse&) -> Mouse& = delete;

    Mouse(Mouse&&) = delete;
    auto operator=(Mouse&&) -> Mouse& = delete;

    virtual auto click(Button button, unsigned int x, unsigned int y) -> void = 0;
};

auto createMouse() -> std::unique_ptr<Mouse>;

} // namespace mouse_clicker
