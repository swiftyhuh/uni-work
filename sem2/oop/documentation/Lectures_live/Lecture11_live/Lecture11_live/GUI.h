#pragma once

#include <QWidget>
#include "ui_GUI.h"
#include "Service.h"

class GUI : public QWidget
{
	Q_OBJECT

public:
	GUI(Service& serv, QWidget *parent = nullptr);
	~GUI();

private:
	Ui::GUIClass ui;
	Service& serv;

	void populateList();
};
