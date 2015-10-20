#include "mycombobox.hpp"


MyComboBox::MyComboBox(QWidget *parent)
    : QComboBox(parent) {}


MyComboBox::~MyComboBox() {}


void MyComboBox::showPopup()
{
    emit popupShown();
    QComboBox::showPopup();
}


void MyComboBox::hidePopup()
{
    QComboBox::hidePopup();
    emit popupHidden();
}
