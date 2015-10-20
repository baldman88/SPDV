#include "portwidgetsimple.hpp"
#include <QDebug>

PortWidgetSimple::PortWidgetSimple(QWidget *parent)
    : QWidget(parent)
{
    uart = new UARTManager(2);

    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(true);

    QLabel *portNameLabel = new QLabel(tr("Port:"), this);
    portName = new MyComboBox(this);

    startButton = new QPushButton(tr("Start"), this);
    stopButton = new QPushButton(tr("Stop"), this);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(portNameLabel, 0, 0);
    mainLayout->addWidget(portName, 0, 1);
    mainLayout->addWidget(startButton, 1, 0);
    mainLayout->addWidget(stopButton, 1, 1);

    setLayout(mainLayout);

    connect(portName, SIGNAL(popupShown()),
            this, SLOT(updatePortsInfo()));

    connect(startButton, SIGNAL(clicked()),
            this, SLOT(uartStart()));

    connect(this, SIGNAL(start(QString)),
            uart, SLOT(start(QString)));

    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(uartStop()));

    connect(this, SIGNAL(stop()),
            uart, SLOT(stop()));

    connect(uart, SIGNAL(started()),
            this, SLOT(uartStarted()));

    connect(uart, SIGNAL(stopped()),
            this, SLOT(uartStopped()));

    connect(uart, SIGNAL(dataReady(QByteArray)),
            this, SLOT(uartDataReady(QByteArray)));

    connect(uart, SIGNAL(showMessage(const char*)),
            this, SIGNAL(showMessage(const char*)));

    connect(timer, SIGNAL(timeout()),
            uart, SLOT(readData()));

    QThread* uartThread = new QThread;
    uart->moveToThread(uartThread);

    connect(uartThread, SIGNAL(finished()),
            uartThread, SLOT(deleteLater()));

    uartThread->start();
}


/* SLOT (private) */
void PortWidgetSimple::updatePortsInfo()
{
    portName->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        portName->addItem(info.portName());
    }
}


/* SLOT (public) */
void PortWidgetSimple::uartStart()
{
    if (portName->currentText() != "")
    {
        emit start(portName->currentText());
    }
    else
    {
        emit showMessage("Set port first.");
    }
}


/* SLOT (public) */
void PortWidgetSimple::uartStop()
{
    timer->stop();
    emit stop();
}


/* SLOT (private) */
void PortWidgetSimple::uartStarted()
{
    startButton->setEnabled(false);
    timer->start(5);
    emit started();
}


/* SLOT (private) */
void PortWidgetSimple::uartStopped()
{
    emit stopped();
    startButton->setEnabled(true);
}


/* SLOT (private) */
void PortWidgetSimple::uartDataReady(QByteArray data)
{
    emit dataReady(data);
    timer->start(2);
}
