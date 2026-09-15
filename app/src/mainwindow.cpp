#include "mainwindow.hpp"

#include "mouse-button.hpp"
#include "mouse.hpp"
#include "ui_mainwindow.h"

#include <QMetaObject>
#include <QString>
#include <array>
#include <cstdint>
#include <string>
#include <utility>


namespace
{

enum class ButtonCombo : std::uint8_t
{
    LEFT,
    RIGHT,
    MIDDLE
};

constexpr auto qtToMouseClickerButton(ButtonCombo button) -> mouse_clicker::Button
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

constexpr std::array<std::pair<ButtonCombo, std::string>, 3> buttonComboToString = {
    { { ButtonCombo::LEFT, "Left" },
     { ButtonCombo::RIGHT, "Right" },
     { ButtonCombo::MIDDLE, "Middle" } }
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
            this, &MainWindow::onStartButtonClicked);
    connect(ui->StopButton, &QPushButton::clicked,
            this, &MainWindow::onStopButtonClicked);

    clicker.setOnStartCallback([this]() {
        QMetaObject::invokeMethod(this, &MainWindow::onMouseClickerStart, Qt::QueuedConnection);
    });
    clicker.setOnStopCallback([this]() {
        QMetaObject::invokeMethod(this, &MainWindow::onMouseClickerStop, Qt::QueuedConnection);
    });

    onMouseClickerStop();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onStartButtonClicked()
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

void MainWindow::onStopButtonClicked()
{
    clicker.stop();
}

void MainWindow::onMouseClickerStart()
{
    this->ui->StartButton->setEnabled(false);
    this->ui->StopButton->setEnabled(true);

    this->ui->CoordsXSpinBox->setReadOnly(true);
    this->ui->CoordsYSpinBox->setReadOnly(true);

    this->ui->ButtonComboBox->setAttribute(Qt::WA_TransparentForMouseEvents);
    this->ui->RepeatsSpinBox->setReadOnly(true);

    this->ui->IntervalMinutesSpinBox->setReadOnly(true);
    this->ui->IntervalSecondsSpinBox->setReadOnly(true);
    this->ui->IntervalMillisecondsSpinBox->setReadOnly(true);
}

void MainWindow::onMouseClickerStop()
{
    this->ui->StartButton->setEnabled(true);
    this->ui->StopButton->setEnabled(false);

    this->ui->CoordsXSpinBox->setReadOnly(false);
    this->ui->CoordsYSpinBox->setReadOnly(false);

    this->ui->ButtonComboBox->setAttribute(Qt::WA_TransparentForMouseEvents, false);
    this->ui->RepeatsSpinBox->setReadOnly(false);

    this->ui->IntervalMinutesSpinBox->setReadOnly(false);
    this->ui->IntervalSecondsSpinBox->setReadOnly(false);
    this->ui->IntervalMillisecondsSpinBox->setReadOnly(false);
}
