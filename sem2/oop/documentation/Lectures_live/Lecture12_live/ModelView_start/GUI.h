#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "MyModel.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(MyModel* model, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;
	MyModel* model;

	void addNewProduct();
	void updateTotal();
};
