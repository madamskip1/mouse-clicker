#pragma once

#include <QMainWindow>
#include <clicker.hpp>
#include <memory>
#include <mouse.hpp>

QT_BEGIN_NAMESPACE
namespace Ui
{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    MainWindow(const MainWindow&) = delete;
    auto operator=(const MainWindow&) -> MainWindow& = delete;

    MainWindow(MainWindow&&) = delete;
    auto operator=(MainWindow&&) -> MainWindow& = delete;

private:
    Ui::MainWindow* ui;

    std::unique_ptr<mouse_clicker::Mouse> mouse;
    mouse_clicker::Clicker clicker;

    void onStartButtonClicked();
    void onStopButtonClicked();

    void onMouseClickerStart();
    void onMouseClickerStop();
};
