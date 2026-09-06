#include "clicker.hpp"

#include <gtest/gtest.h>

TEST(Clicker, Start)
{
    mouse_clicker::Clicker clicker;

    clicker.start();

    EXPECT_TRUE(clicker.isRunning());
}

TEST(Clicker, TryStartWhenAlreadyRunning)
{
    mouse_clicker::Clicker clicker;

    clicker.start();

    EXPECT_DEATH(clicker.start(), "");
}

TEST(Clicker, Stop)
{
    mouse_clicker::Clicker clicker;
    clicker.start();

    clicker.stop();

    EXPECT_FALSE(clicker.isRunning());
}

TEST(Clicker, TryStopWhenNotRunning)
{
    mouse_clicker::Clicker clicker;

    EXPECT_DEATH(clicker.stop(), "");
}
