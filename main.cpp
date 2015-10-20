#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.resize(QSize(1000, 500));

    mainWindow.show();

    return app.exec();
}
