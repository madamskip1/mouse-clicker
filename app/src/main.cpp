#include "mainwindow.hpp"

#include <QApplication>

auto main(int argc, char* argv[]) -> int
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return QApplication::exec();
}
