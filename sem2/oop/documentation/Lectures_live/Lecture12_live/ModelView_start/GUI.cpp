#include "GUI.h"

GUI::GUI(MyModel* model, QWidget *parent)
	: QWidget(parent), model{model}
{
	ui.setupUi(this);
	ui.tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui.tableView->setModel(this->model);

	ui.totalLineEdit->setText(QString::number(model->getTotal()));

	QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &GUI::addNewProduct);
	QObject::connect(this->model, &MyModel::updateTotalSignal, this, &GUI::updateTotal);
}

GUI::~GUI()
{}

void GUI::addNewProduct()
{
	// read name, price
	this->model->addProduct("Honey", 35);
}

void GUI::updateTotal()
{
	ui.totalLineEdit->setText(QString::number(model->getTotal()));
}
