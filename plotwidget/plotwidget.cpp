#include "plotwidget/plotwidget.hpp"


PlotWidget::PlotWidget(QWidget* parent)
    : QWidget(parent)
{
    minValue = 0.0;
    maxValue = 3.5;

    plotArea = new QCustomPlot(this);
    plotArea->addGraph();
    plotArea->graph(0)->setPen(QPen(Qt::red));
    plotArea->graph(0)->setAntialiasedFill(true);
    plotArea->xAxis->setTickLabelType(QCPAxis::ltDateTime);
    plotArea->xAxis->setDateTimeFormat("hh:mm:ss");
    plotArea->xAxis->setAutoTickStep(true);
    plotArea->yAxis->setAutoTickStep(false);
    plotArea->yAxis->setTickStep(0.25);
    plotArea->yAxis->setRange(minValue, maxValue);
    plotArea->axisRect()->setupFullAxesBox();
    connect(plotArea->xAxis, SIGNAL(rangeChanged(QCPRange)),
            plotArea->xAxis2, SLOT(setRange(QCPRange)));
    connect(plotArea->yAxis, SIGNAL(rangeChanged(QCPRange)),
            plotArea->yAxis2, SLOT(setRange(QCPRange)));

    yAxisBottomValue = new QDoubleSpinBox(this);
    yAxisBottomValue->setDecimals(2);
    yAxisBottomValue->setSingleStep(0.25);
    yAxisBottomValue->setValue(minValue);

    yAxisTopValue = new QDoubleSpinBox(this);
    yAxisTopValue->setDecimals(2);
    yAxisTopValue->setSingleStep(0.25);
    yAxisTopValue->setValue(maxValue);

    yAxisBottomValue->setRange(0.0, (maxValue - 0.25));
    yAxisTopValue->setRange((minValue + 0.25), 3.5);

    yAxisSetAutoscaleButton = new QCheckBox(this);
    yAxisSetAutoscaleButton->setText(tr("Autoscale"));

    yAxisSetDefaultsButton = new QPushButton(tr("Set defaults"), this);

    QLabel* rangeLabel = new QLabel(tr("Range:"), this);
    QGridLayout* rangeLayout = new QGridLayout;
    rangeLayout->addWidget(rangeLabel, 0, 0, 2, 1);
    rangeLayout->addWidget(yAxisTopValue, 0, 1, 1, 1);
    rangeLayout->addWidget(yAxisBottomValue, 1, 1, 1, 1);

    QHBoxLayout* controlLayout = new QHBoxLayout;
    controlLayout->addLayout(rangeLayout);
    controlLayout->addStretch();
    controlLayout->addWidget(yAxisSetAutoscaleButton);
    controlLayout->addStretch();
    controlLayout->addWidget(yAxisSetDefaultsButton);
    controlLayout->setAlignment(Qt::AlignHCenter);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(controlLayout);
    mainLayout->addWidget(plotArea);

    setLayout(mainLayout);

    connect(yAxisSetAutoscaleButton, SIGNAL(stateChanged(int)),
            this, SLOT(yAxisSetAutoscale(int)));

    connect(yAxisSetDefaultsButton, SIGNAL(clicked()),
            this, SLOT(yAxisSetDefaults()));

    connect(yAxisBottomValue, SIGNAL(valueChanged(double)),
            this, SLOT(yAxisBottomRangeChanged(double)));

    connect(yAxisTopValue, SIGNAL(valueChanged(double)),
            this, SLOT(yAxisTopRangeChanged(double)));

    //plotArea->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
}


void PlotWidget::updatePlotArea(float data)
{
    //double x = (QDateTime::currentDateTime().toMSecsSinceEpoch() / 1000.0);
    double x = ((QDateTime::currentDateTime().toMSecsSinceEpoch() - startTime) / 1000.0);
    plotArea->graph(0)->removeDataBefore(x - 8);
    plotArea->graph(0)->addData(x, data);
    plotArea->graph(0)->rescaleValueAxis();
    if (!yAxisSetAutoscaleButton->isChecked())
    {
        plotArea->yAxis->setRange(minValue, maxValue);
    }
    plotArea->xAxis->setRange(x + 0.25, 8, Qt::AlignRight);
    plotArea->replot();
}


void PlotWidget::clearPlotArea()
{
    plotArea->graph(0)->clearData();
    startTime = QDateTime::currentDateTime().toMSecsSinceEpoch() + 7200000;
}


void PlotWidget::yAxisSetAutoscale(int state)
{
    if (state == 0)
    {
        plotArea->yAxis->setAutoTickStep(false);
        if ((maxValue - minValue) == 0.25)
        {
            plotArea->yAxis->setTickStep(0.05);
        }
        else
        {
            plotArea->yAxis->setTickStep(0.25);
        }
        yAxisBottomValue->setEnabled(true);
        yAxisTopValue->setEnabled(true);
    }
    else
    {
        plotArea->yAxis->setAutoTickStep(true);
        yAxisBottomValue->setEnabled(false);
        yAxisTopValue->setEnabled(false);
    }
}


void PlotWidget::yAxisSetDefaults()
{
    yAxisBottomValue->setValue(0.0);
    minValue = 0.0;
    yAxisTopValue->setValue(3.5);
    maxValue = 3.5;
    plotArea->yAxis->setTickStep(0.25);
    yAxisSetAutoscaleButton->setChecked(false);
}


void PlotWidget::yAxisBottomRangeChanged(double value)
{
    minValue = value;
    yAxisTopValue->setRange((minValue + 0.25), 3.5);
    if ((maxValue - minValue) == 0.25)
    {
        plotArea->yAxis->setTickStep(0.05);
    }
    else
    {
        plotArea->yAxis->setTickStep(0.25);
    }
}


void PlotWidget::yAxisTopRangeChanged(double value)
{
    maxValue = value;
    yAxisBottomValue->setRange(0.0, (maxValue - 0.25));
    if ((maxValue - minValue) == 0.25)
    {
        plotArea->yAxis->setTickStep(0.05);
    }
    else
    {
        plotArea->yAxis->setTickStep(0.25);
    }
}
