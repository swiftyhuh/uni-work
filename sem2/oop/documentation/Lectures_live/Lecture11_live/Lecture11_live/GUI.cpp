#include "GUI.h"

GUI::GUI(Service& serv, QWidget *parent)
	: QWidget(parent), serv{serv}
{
	ui.setupUi(this);
	this->populateList();
}

GUI::~GUI()
{}

void GUI::populateList()
{
	std::vector<Spaceship> elems = this->serv.getAll();
	for (auto& s : elems)
	{
		QString str = QString::fromStdString(s.getName() + ", " + s.getCaptain() + ", " + s.getType());
		this->ui.spaceshipsListWidget->addItem(str);
	}
}
