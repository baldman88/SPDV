#ifndef MYCOMBOBOX_HPP
#define MYCOMBOBOX_HPP


#include <QComboBox>
#include <cmath>


class MyComboBox: public QComboBox
{
    Q_OBJECT

public:
    MyComboBox(QWidget  *parent = 0);
    ~MyComboBox();

signals:
    void popupShown();
    void popupHidden();

protected:
    void showPopup();
    void hidePopup();
};


#endif // MYCOMBOBOX_HPP
