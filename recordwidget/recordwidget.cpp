#include "recordwidget.hpp"


RecordWidget::RecordWidget(QWidget* parent)
    : QWidget(parent)
{
    file = new QFile();

    time = new QTime;
    time->start();

    timer = new QTimer;
    timer->setTimerType(Qt::PreciseTimer);
    timer->setSingleShot(true);

    enableFlag = false;
    recordFlag = false;

    recordCounter = 0;

    fileChooserDialog = new QFileDialog(this, tr("Open file"), "/home/baldman/projects/spdv_data", "Data files (*.txt *.csv)");
//    fileChooserDialog = new QFileDialog;
//    fileChooserDialog->setModal(false);
//    fileChooserDialog->setWindowModality(Qt::NonModal);
//    fileChooserDialog->setDirectory("/home/baldman/projects/spdv_data");
//    fileChooserDialog->setNameFilter("Data files (*.txt)");
    fileChooserDialog->setViewMode(QFileDialog::List);

    QLabel* fileLabel = new QLabel(tr("File:"), this);
    filePath = new QLineEdit(this);

    fileChooserButton = new QPushButton("...", this);
    fileChooserButton->setFixedWidth(35);

    QHBoxLayout* filePathLayout = new QHBoxLayout;
    filePathLayout->addWidget(fileLabel);
    filePathLayout->addWidget(filePath);
    filePathLayout->addWidget(fileChooserButton);

    setTimeButton = new QRadioButton(tr("Set time (s):"), this);
    setTimeButton->setChecked(true);
    setPointsButton = new QRadioButton(tr("Set points:"), this);
    setPermanentlyButton = new QRadioButton(tr("Record permanently"), this);

    QButtonGroup* setPeriodButtonsGroup = new QButtonGroup(this);
    setPeriodButtonsGroup->addButton(setTimeButton);
    setPeriodButtonsGroup->addButton(setPointsButton);
    setPeriodButtonsGroup->addButton(setPermanentlyButton);

    pointsSpinBox = new QSpinBox(this);
    pointsSpinBox->setRange(1, std::numeric_limits<int>::max());
    pointsSpinBox->setValue(100);
    timeSpinBox = new QSpinBox(this);
    timeSpinBox->setRange(1, std::numeric_limits<int>::max());
    timeSpinBox->setValue(10);

    startButton = new QPushButton(tr("Start"), this);
    stopButton = new QPushButton(tr("Stop"), this);

    progressBar = new QProgressBar(this);
    progressBar->setRange(0,100);
    QLabel* recordLabel = new QLabel(tr("Record:"), this);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(startButton);
    buttonsLayout->addWidget(stopButton);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addLayout(filePathLayout, 0, 0, 1, 6);
    mainLayout->addWidget(setTimeButton, 1, 0, 1, 3);
    mainLayout->addWidget(timeSpinBox, 1, 3, 1, 3);
    mainLayout->addWidget(setPointsButton, 2, 0, 1, 3);
    mainLayout->addWidget(pointsSpinBox, 2, 3, 1, 3);
    mainLayout->addWidget(setPermanentlyButton, 3, 0, 1, 6);
    mainLayout->addLayout(buttonsLayout, 4, 0, 1, 6);
    mainLayout->addWidget(recordLabel, 5, 0, 1, 1);
    mainLayout->addWidget(progressBar, 5, 1, 1, 5);

    setLayout(mainLayout);

    connect(fileChooserButton, SIGNAL(clicked()),
            fileChooserDialog, SLOT(show()));

    connect(fileChooserDialog, SIGNAL(fileSelected(QString)),
            filePath, SLOT(setText(QString)));

    connect(startButton, SIGNAL(clicked()),
            this, SLOT(startRecord()));

    connect(stopButton, SIGNAL(clicked()),
            this, SLOT(stopRecord()));

    connect(timer, SIGNAL(timeout()),
            this, SLOT(stopRecord()));
}


/* SLOT (public) */
void RecordWidget::writeData(float data)
{
    if (recordFlag)
    {
        //file->write(QString("%1;").arg(data).toStdString().c_str());
        file->write(QString("%1\t%2\n").arg(QString("%1").arg(time->elapsed()/1000.0).replace(".", ",")).arg(QString("%1").arg(data).replace(".", ",")).toStdString().c_str());
        if (setTimeButton->isChecked())
        {
            recordCounter = recordCycles - timer->remainingTime();
        }
        else
        {
            recordCounter++;
        }
        progressBar->setValue(recordCounter);
        if ((recordCounter == recordCycles) && setPointsButton->isChecked())
        {
            stopRecord();
        }
    }
}


/* SLOT (private) */
void RecordWidget::enableRecord()
{
    enableFlag = true;
}


/* SLOT (private) */
void RecordWidget::disableRecord()
{
    enableFlag = false;
}


/* SLOT (private) */
void RecordWidget::startRecord()
{
    if (enableFlag)
    {
        if (filePath->text() != "")
        {
            file->setFileName(filePath->text());
            if (file->open(QIODevice::WriteOnly | QIODevice::Text))
            {
                if (setPermanentlyButton->isChecked())
                {
                    progressBar->setRange(0, 0);
                }
                else if (setPointsButton->isChecked())
                {
                    recordCycles = pointsSpinBox->value();
                    progressBar->setRange(0, recordCycles);
                }
                else
                {
                    recordCycles = (int)(timeSpinBox->value() * 1000);
                    progressBar->setRange(0, recordCycles);
                    timer->setInterval(timeSpinBox->value() * 1000);
                    timer->start();
                }
                time->restart();
                recordFlag = true;
                startButton->setEnabled(false);
            }
            else
            {
                emit showMessage("Could not open file!");
            }
        }
        else
        {
            emit showMessage("Please, set file to write!");
        }
    }
    else
    {
        emit showMessage("Nothing to write. Start reading first!");
    }
}


/* SLOT (private) */
void RecordWidget::stopRecord()
{
    recordFlag = false;
    if (timer->isActive())
    {
        timer->stop();
    }
    progressBar->reset();
    progressBar->setRange(0, 100);
    startButton->setEnabled(true);
    file->close();
    recordCounter = 0;
}
