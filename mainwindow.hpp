#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "plotwidget/plotwidget.hpp"
#include "recordwidget/recordwidget.hpp"
#include "portwidgetsimple/portwidgetsimple.hpp"
#include <QLabel>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSerialPortInfo>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private slots:
    void readData(QByteArray data);
    void showMessageBox(const char *message);
    void portStarted();
    void portStopped();

private:
    PortWidgetSimple    *portWidget;
    PlotWidget          *plotWidget;
    RecordWidget        *recordWidget;
    QMessageBox         *messageBox;
};

#endif /* MAINWINDOW_HPP */
