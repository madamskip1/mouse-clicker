#pragma once

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

    virtual auto click(unsigned int x, unsigned int y) -> void = 0;
};

} // namespace mouse_clicker
