#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lecture9_demo_widgets.h"

class Lecture9_demo_widgets : public QMainWindow
{
    Q_OBJECT

public:
    Lecture9_demo_widgets(QWidget *parent = nullptr);
    ~Lecture9_demo_widgets();

private:
    Ui::Lecture9_demo_widgetsClass ui;
};
