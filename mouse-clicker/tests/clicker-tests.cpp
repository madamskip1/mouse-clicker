#include "clicker.hpp"
#include "mouse-button.hpp"
#include "mouse.hpp"

#include <chrono>
#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <memory>
#include <thread>

using namespace std::chrono_literals;


class MockMouse : public mouse_clicker::Mouse
{
public:
    MockMouse() = default;

    MOCK_METHOD(void, click, (mouse_clicker::Button, unsigned int, unsigned int), (override));
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
    clicker->setRepeats(0);

    clicker->start();

    EXPECT_TRUE(clicker->isRunning());

    clicker->stop();
}

TEST_F(ClickerTest, Stop)
{
    clicker->setRepeats(0);
    clicker->start();

    clicker->stop();

    EXPECT_FALSE(clicker->isRunning());
}

TEST_F(ClickerTest, StopInterval)
{
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_, testing::_)).Times(1); // first click is immediately
    clicker->setRepeats(0);
    clicker->setInterval(1000ms);
    clicker->start();
    std::this_thread::sleep_for(10ms); // To be sure that the first click is done

    const auto beforeStop = std::chrono::steady_clock::now();
    clicker->stop();
    const auto elapsed = std::chrono::steady_clock::now() - beforeStop;

    EXPECT_LT(std::chrono::duration_cast<std::chrono::milliseconds>(elapsed), 50ms);
}

TEST_F(ClickerTest, ClickOnce)
{
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_, testing::_)).Times(1);

    clicker->setRepeats(1u);

    clicker->start();
    std::this_thread::sleep_for(10ms);
}

TEST_F(ClickerTest, ClickRepeat)
{
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_, testing::_)).Times(5);

    clicker->setRepeats(5u);

    clicker->start();
    std::this_thread::sleep_for(10ms);
}

TEST_F(ClickerTest, SetCoords)
{
    clicker->setRepeats(1);
    EXPECT_CALL(*mouseMock, click(testing::_, 5u, 10u));

    clicker->setCoords(5u, 10u);

    clicker->start();
    std::this_thread::sleep_for(10ms);
}

TEST_F(ClickerTest, SetButton)
{
    EXPECT_CALL(*mouseMock, click(mouse_clicker::Button::RIGHT, testing::_, testing::_));

    clicker->setButton(mouse_clicker::Button::RIGHT);

    clicker->start();
    std::this_thread::sleep_for(10ms);
}

TEST_F(ClickerTest, SetInterval)
{
    clicker->setRepeats(10); // doesn't matter, we stop after 3 clicks
    EXPECT_CALL(*mouseMock, click(testing::_, testing::_, testing::_)).Times(3);

    clicker->setInterval(30ms);

    clicker->start();
    std::this_thread::sleep_for(75ms); // Clicked when starting, then twice after 30ms and 60ms
    clicker->stop();
}
