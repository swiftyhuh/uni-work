#pragma once

#include <QtWidgets/QWidget>
#include "ui_Lecture10_live.h"

class Lecture10_live : public QWidget
{
    Q_OBJECT

public:
    Lecture10_live(QWidget *parent = nullptr);
    ~Lecture10_live();

private:
    Ui::Lecture10_liveClass ui;
};
