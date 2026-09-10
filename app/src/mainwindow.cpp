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
    clicker.start();
}

void MainWindow::on_StopButton_clicked()
{
    clicker.stop();
}
