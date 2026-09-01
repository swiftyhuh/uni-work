#pragma once

#include <QtWidgets/QWidget>
#include "ui_Lecture10_genes_demo.h"

class Lecture10_genes_demo : public QWidget
{
    Q_OBJECT

public:
    Lecture10_genes_demo(QWidget *parent = nullptr);
    ~Lecture10_genes_demo();

private:
    Ui::Lecture10_genes_demoClass ui;
};
