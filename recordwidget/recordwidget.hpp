#ifndef RECORDWIDGET_HPP
#define RECORDWIDGET_HPP

#include <limits>
#include <QTime>
#include <QLabel>
#include <QTimer>
#include <QWidget>
#include <QThread>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QRadioButton>
#include <QProgressBar>
#include <QButtonGroup>

class RecordWidget: public QWidget
{
    Q_OBJECT

public:
    RecordWidget(QWidget* parent = 0);

signals:
    void showMessage(const char *message);

public slots:
    void writeData(float data);
    void enableRecord();
    void disableRecord();

private slots:
    void startRecord();
    void stopRecord();

private:
    QPushButton*  startButton;
    QPushButton*  stopButton;
    QPushButton*  fileChooserButton;
    QLineEdit*    filePath;
    QFileDialog*  fileChooserDialog;
    QRadioButton* setTimeButton;
    QRadioButton* setPointsButton;
    QRadioButton* setPermanentlyButton;
    QSpinBox*     timeSpinBox;
    QSpinBox*     pointsSpinBox;
    QProgressBar* progressBar;
    QFile*        file;
    QTimer*       timer;
    QTime*        time;
    bool          recordFlag;
    bool          enableFlag;
    int           recordCounter;
    int           recordCycles;
};


#endif /* RECORDWIDGET_HPP */
