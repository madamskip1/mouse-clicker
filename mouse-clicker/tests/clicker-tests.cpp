#include "clicker.hpp"
#include "mouse.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>

class MockMouse : public mouse_clicker::Mouse
{
public:
    MockMouse() = default;

    MOCK_METHOD(void, click, (unsigned int, unsigned int), (override));
};

class ClickerTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        mouseMock = std::make_unique<MockMouse>();
        clicker = std::make_unique<mouse_clicker::Clicker>(*mouseMock);
    }

    std::unique_ptr<MockMouse> mouseMock;
    std::unique_ptr<mouse_clicker::Clicker> clicker;
};

TEST_F(ClickerTest, Start)
{
    GTEST_SKIP() << "Right now loop is not in separate thread";

    clicker->start();

    EXPECT_TRUE(clicker->isRunning());
}

TEST_F(ClickerTest, TryStartWhenAlreadyRunning)
{
    GTEST_SKIP() << "Right now loop is not in separate thread";

    clicker->start();

    EXPECT_DEATH(clicker->start(), "");
}

TEST_F(ClickerTest, Stop)
{
    GTEST_SKIP() << "Right now loop is not in separate thread";
    clicker->start();

    clicker->stop();

    EXPECT_FALSE(clicker->isRunning());
}

TEST_F(ClickerTest, TryStopWhenNotRunning)
{
    GTEST_SKIP() << "Right now loop is not in separate thread";

    EXPECT_DEATH(clicker->stop(), "");
}

TEST_F(ClickerTest, ClickOnce)
{
    clicker->setRepeats(1u);
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_)).Times(1);

    clicker->start();
}

TEST_F(ClickerTest, ClickRepeat)
{
    clicker->setRepeats(5u);
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_)).Times(5);

    clicker->start();
}

TEST_F(ClickerTest, TrySetRepeatsWhenRunning)
{
    GTEST_SKIP() << "Right now loop is not in separate thread";

    clicker->start();

    EXPECT_DEATH(clicker->setRepeats(5u), "");
}
