#ifndef PLOTWIDGET_HPP
#define PLOTWIDGET_HPP

#include "qcustomplot/qcustomplot.hpp"
#include <limits>
#include <QLabel>
#include <QWidget>
#include <QCheckBox>
#include <QDateTime>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QSpacerItem>
#include <QDoubleSpinBox>


class PlotWidget : public QWidget
{
    Q_OBJECT

public:
    PlotWidget(QWidget* parent = 0);
    void updatePlotArea(float data);
    void clearPlotArea();

private slots:
    void yAxisSetAutoscale(int state);
    void yAxisSetDefaults();
    void yAxisBottomRangeChanged(double value);
    void yAxisTopRangeChanged(double value);

private:
    QCustomPlot*    plotArea;
    QDoubleSpinBox* yAxisTopValue;
    QDoubleSpinBox* yAxisBottomValue;
    QPushButton*    yAxisSetDefaultsButton;
    QCheckBox*      yAxisSetAutoscaleButton;
    double          minValue;
    double          maxValue;
    double          startTime;
};


#endif /* PLOTWIDGET_HPP */
