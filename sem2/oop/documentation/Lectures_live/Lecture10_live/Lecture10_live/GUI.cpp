#include "GUI.h"
#include <QHBoxLayout>
#include <qgridlayout.h>
#include <qlabel.h>

GUI::GUI(Service& serv): serv{serv}
{
	this->buildGUI();
	this->populateList();

	QObject::connect(this->addButton, &QPushButton::clicked, 
		this, &GUI::add);
}

void GUI::buildGUI()
{
	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	this->spaceshipsList = new QListWidget{};
	mainLayout->addWidget(this->spaceshipsList);

	QGridLayout* rightLayout = new QGridLayout{};
	QLabel* nameLabel = new QLabel{ "Name" };
	QLabel* captainLabel = new QLabel{ "Captain" };
	QLabel* typeLabel = new QLabel{ "Type" };
	this->nameEdit = new QLineEdit{};
	this->captainEdit = new QLineEdit{};
	this->typeEdit = new QLineEdit{};

	rightLayout->addWidget(nameLabel, 0, 0);
	rightLayout->addWidget(nameEdit, 0, 1);
	rightLayout->addWidget(captainLabel, 1, 0);
	rightLayout->addWidget(captainEdit, 1, 1);
	rightLayout->addWidget(typeLabel, 2, 0);
	rightLayout->addWidget(typeEdit, 2, 1);

	this->addButton = new QPushButton{ "Add" };
	this->removeButton = new QPushButton{ "Remove" };
	rightLayout->addWidget(this->addButton, 3, 0);
	rightLayout->addWidget(this->removeButton, 3, 1);

	mainLayout->addLayout(rightLayout);
}

void GUI::populateList()
{
	this->spaceshipsList->clear();
	std::vector<Spaceship> spaceships = this->serv.getAll();
	for (auto& s : spaceships) {
		std::string str = s.getName() + ", " + s.getCaptain() + ", " + s.getType();
		this->spaceshipsList->addItem(QString::fromStdString(str));
	}
}

void GUI::add()
{
	QString name = this->nameEdit->text();
	QString captain = this->captainEdit->text();
	QString type = this->typeEdit->text();
	this->serv.add(name.toStdString(), type.toStdString(), captain.toStdString());
	this->populateList();
}
