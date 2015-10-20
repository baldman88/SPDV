#ifndef UART_MANAGER_HPP
#define UART_MANAGER_HPP


//#include <QtSerialPort/QSerialPort>
#include <QSerialPort>
#include <QByteArray>
#include <QTimer>
#include "crc16/crc16.hpp"


class UARTManager: public QObject
{
    Q_OBJECT

public:
    UARTManager(int data_size, QObject* parent = 0);
    ~UARTManager();

signals:
    void started();
    void stopped();
    void dataReady(QByteArray data);
    void showMessage(const char *message);

public slots:
    void start(QString portName);
    void stop();
    void readData();

private slots:
    void sendRequset();
    void readResponse();

private:
    QSerialPort* UART;
    char*        buffer;
    int          buffer_size;
    bool         checkCRC16(char* buffer, int data_size);
};


#endif /* UART_MANAGER_HPP */
