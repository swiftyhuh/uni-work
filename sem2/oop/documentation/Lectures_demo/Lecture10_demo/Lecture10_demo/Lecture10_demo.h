#pragma once

#include <QtWidgets/QWidget>
#include "ui_Lecture10_demo.h"

class Lecture10_demo : public QWidget
{
    Q_OBJECT

public:
    Lecture10_demo(QWidget *parent = nullptr);
    ~Lecture10_demo();

private:
    Ui::Lecture10_demoClass ui;
};
