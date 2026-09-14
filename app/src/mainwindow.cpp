#include "mainwindow.hpp"

#include "mouse-button.hpp"
#include "mouse.hpp"
#include "ui_mainwindow.h"

#include <QString>
#include <cstdint>
#include <unordered_map>

namespace
{

enum class ButtonCombo : std::uint8_t
{
    LEFT,
    RIGHT,
    MIDDLE
};

static constexpr auto qtToMouseClickerButton(ButtonCombo button) -> mouse_clicker::Button
{
    switch (button)
    {
    case ButtonCombo::LEFT:
        return mouse_clicker::Button::LEFT;
    case ButtonCombo::RIGHT:
        return mouse_clicker::Button::RIGHT;
    case ButtonCombo::MIDDLE:
        return mouse_clicker::Button::MIDDLE;
    default:
        assert(false);
    }
}

static const std::unordered_map<ButtonCombo, std::string> buttonComboToString = {
    {   ButtonCombo::LEFT,   "Left" },
    {  ButtonCombo::RIGHT,  "Right" },
    { ButtonCombo::MIDDLE, "Middle" }
};

} // namespace

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mouse(mouse_clicker::createMouse()),
      clicker(*mouse)
{
    ui->setupUi(this);

    for (const auto& [button, buttonString] : buttonComboToString)
    {
        ui->ButtonComboBox->addItem(QString::fromStdString(buttonString), std::to_underlying(button));
    }

    connect(ui->StartButton, &QPushButton::clicked,
            this, &MainWindow::on_StartButton_clicked);
    connect(ui->StopButton, &QPushButton::clicked,
            this, &MainWindow::on_StopButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_StartButton_clicked()
{
    const auto repeatsValue = ui->RepeatsSpinBox->value();
    clicker.setRepeats(repeatsValue);

    const auto intervalMilisecondsValue = std::chrono::milliseconds(ui->IntervalMillisecondsSpinBox->value());
    const auto intervalSecondsValue = std::chrono::seconds(ui->IntervalSecondsSpinBox->value());
    const auto intervalMinutesValue = std::chrono::minutes(ui->IntervalMinutesSpinBox->value());
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(intervalSecondsValue + intervalMinutesValue + intervalMilisecondsValue);
    clicker.setInterval(duration);

    const auto coordsX = ui->CoordsXSpinBox->value();
    const auto coordsY = ui->CoordsYSpinBox->value();
    clicker.setCoords(coordsX, coordsY);

    const auto button = qtToMouseClickerButton(ui->ButtonComboBox->currentData().value<ButtonCombo>());
    clicker.setButton(button);

    clicker.start();
}

void MainWindow::on_StopButton_clicked()
{
    clicker.stop();
}
