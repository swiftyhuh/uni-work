#pragma once

#include <QtWidgets/QWidget>
#include "ui_Lecture11_live.h"

class Lecture11_live : public QWidget
{
    Q_OBJECT

public:
    Lecture11_live(QWidget *parent = nullptr);
    ~Lecture11_live();

private:
    Ui::Lecture11_liveClass ui;
};
