#include "mouse-button.hpp"
#include "mouse.hpp"

namespace mouse_clicker
{
class MouseLinux final : public Mouse
{
public:
    MouseLinux() = default;

    auto click(Button button, unsigned int x, unsigned int y) -> void final;
};
} // namespace mouse_clicker
