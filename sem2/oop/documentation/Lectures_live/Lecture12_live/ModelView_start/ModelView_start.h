#pragma once

#include <QtWidgets/QWidget>
#include "ui_ModelView_start.h"

class ModelView_start : public QWidget
{
    Q_OBJECT

public:
    ModelView_start(QWidget *parent = nullptr);
    ~ModelView_start();

private:
    Ui::ModelView_startClass ui;
};
