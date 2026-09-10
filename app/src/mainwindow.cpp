#include "mainwindow.hpp"

#include "mouse-linux.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      mouse(std::make_unique<mouse_clicker::MouseLinux>()),
      clicker(*mouse)
{
    ui->setupUi(this);

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

    clicker.start();
}

void MainWindow::on_StopButton_clicked()
{
    clicker.stop();
}
