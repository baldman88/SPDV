#include "uartmanager.hpp"
#include <QDebug>

#define CRC16_SIZE 2

UARTManager::UARTManager(int data_size, QObject* parent)
    : QObject(parent)
{
    UART = new QSerialPort(this);

    buffer_size = data_size + CRC16_SIZE;
    buffer = new char[buffer_size];

    connect(UART, SIGNAL(readyRead()),
            this, SLOT(readResponse()));
}


UARTManager::~UARTManager()
{
    delete[] buffer;
}


/* SLOT (public) */
void UARTManager::start(QString portName)
{
    UART->setPortName(portName);
    if (UART->open(QIODevice::ReadWrite))
    {
        UART->setBaudRate(115200);
        UART->setDataBits(QSerialPort::Data8);
        UART->setStopBits(QSerialPort::TwoStop);
        UART->setParity(QSerialPort::NoParity);
        UART->setFlowControl(QSerialPort::NoFlowControl);
        UART->clear();
        emit started();
    }
    else
    {
        emit showMessage("Could not open port!");
    }
}


/* SLOT (public) */
void UARTManager::stop()
{
    if (UART->isOpen())
    {
        UART->clear();
        UART->close();
    }
    emit stopped();
}


/* SLOT (public) */
void UARTManager::readData()
{
    sendRequset();
}


/* SLOT (private) */
void UARTManager::sendRequset()
{
    if (UART->isOpen())
    {
        UART->write(QByteArray(2, 0x0F), 2);
    }
}


/* SLOT (private) */
void UARTManager::readResponse()
{
    if (UART->isOpen())
    {
        if (UART->bytesAvailable() >= buffer_size)
        {
            QByteArray data = UART->read(buffer_size);
            if (checkCRC16(data.data(), (buffer_size - CRC16_SIZE)))
            {
                emit dataReady(data.mid(0, (buffer_size - CRC16_SIZE)));
            }
        }
    }
}


bool UARTManager::checkCRC16(char* buffer, int data_size)
{
    uint16_t CRC16 = (uint16_t)((uint8_t)buffer[data_size] | ((uint8_t)buffer[(data_size + 1)] << 8));
    if (Calculate((uint8_t*)buffer, data_size) == CRC16)
    {
        return true;
    }
    else
    {
        return false;
    }
}
