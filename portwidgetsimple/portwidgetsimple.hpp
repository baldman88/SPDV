#ifndef PORTWIDGETSIMPLE_HPP
#define PORTWIDGETSIMPLE_HPP

#include <QTimer>
#include <QLabel>
#include <QWidget>
#include <QThread>
#include <QSpinBox>
#include <QComboBox>
#include <QByteArray>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QtSerialPort/QSerialPortInfo>

#include "../mycombobox/mycombobox.hpp"
#include "../uartmanager/uartmanager.hpp"

class PortWidgetSimple: public QWidget
{
    Q_OBJECT

public:
    PortWidgetSimple(QWidget *parent = 0);

signals:
    void start(QString portName);
    void stop();
    void started();
    void stopped();
    void dataReady(QByteArray data);
    void showMessage(const char *message);

private slots:
    void uartStart();
    void uartStop();
    void uartStarted();
    void uartStopped();
    void updatePortsInfo();
    void uartDataReady(QByteArray data);

private:
    QTimer                *timer;
    UARTManager           *uart;
    MyComboBox            *portName;
    QPushButton           *startButton;
    QPushButton           *stopButton;
};


#endif /* PORTWIDGETSIMPLE_HPP */
