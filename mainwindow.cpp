#include "mainwindow.hpp"
#include <limits>


MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget(this);

    messageBox = new QMessageBox(this);
    messageBox->addButton(QMessageBox::Ok);

    portWidget = new PortWidgetSimple(this);

    recordWidget = new RecordWidget(this);

    plotWidget = new PlotWidget(this);

    QGroupBox* portBox = new QGroupBox(tr("Port:"), this);
    QVBoxLayout* portLayout = new QVBoxLayout;
    portLayout->addWidget(portWidget);
    portBox->setLayout(portLayout);
    portBox->setFixedWidth(310);
    portBox->setAlignment(Qt::AlignCenter);

    QGroupBox* recordBox = new QGroupBox(tr("Record:"), this);
    QVBoxLayout* recordLayout = new QVBoxLayout;
    recordLayout->addWidget(recordWidget);
    recordBox->setLayout(recordLayout);
    recordBox->setFixedWidth(310);
    recordBox->setAlignment(Qt::AlignCenter);

    QVBoxLayout* controlLayout = new QVBoxLayout;
    controlLayout->addWidget(portBox);
    controlLayout->addWidget(recordBox);
    controlLayout->setAlignment(Qt::AlignTop);

    QGroupBox* plotBox = new QGroupBox(this);
    QHBoxLayout* plotLayout = new QHBoxLayout;
    plotLayout->addWidget(plotWidget);
    plotBox->setLayout(plotLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(plotBox);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    setWindowTitle(tr("SPDV"));

    connect(portWidget, SIGNAL(started()),
            this, SLOT(portStarted()));

    connect(portWidget, SIGNAL(stopped()),
            this, SLOT(portStopped()));

    connect(portWidget, SIGNAL(dataReady(QByteArray)),
            this, SLOT(readData(QByteArray)));

    connect(portWidget, SIGNAL(showMessage(const char*)),
            this, SLOT(showMessageBox(const char*)));

    connect(recordWidget, SIGNAL(showMessage(const char*)),
            this, SLOT(showMessageBox(const char*)));
}


/* SLOT (private) */
void MainWindow::readData(QByteArray data)
{
    float result = (float)(((uint16_t)((uint8_t)data[0] | ((uint8_t)data[1] << 8))) * 0.000805664);
    recordWidget->writeData(result);
    plotWidget->updatePlotArea(result);
}


/* SLOT (private) */
void MainWindow::showMessageBox(const char* message)
{
    messageBox->setText(tr(message));
    messageBox->show();
}


/* SLOT (private) */
void MainWindow::portStarted()
{
    recordWidget->enableRecord();
    plotWidget->clearPlotArea();
}


/* SLOT (private) */
void MainWindow::portStopped()
{
    recordWidget->disableRecord();
}
