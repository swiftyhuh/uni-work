#pragma once
#include <qwidget.h>
#include "Service.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class GUI: public QWidget
{
private:
	Service& serv;

	QListWidget* spaceshipsList;
	QLineEdit* nameEdit;
	QLineEdit* captainEdit;
	QLineEdit* typeEdit;
	QPushButton* addButton;
	QPushButton* removeButton;

public:
	GUI(Service& serv);
	void buildGUI();
	void populateList();
	void add();
};

