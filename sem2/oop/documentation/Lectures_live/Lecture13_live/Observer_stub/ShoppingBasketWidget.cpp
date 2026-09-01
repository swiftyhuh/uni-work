#include "ShoppingBasketWidget.h"

ShoppingBasketWidget::ShoppingBasketWidget(Service& serv, QWidget *parent)
	: QWidget(parent), serv{serv}
{
	ui.setupUi(this);
	this->populateList();
	this->ui.totalLineEdit->setText(QString::number(this->serv.getTotal()));

	QObject::connect(this->ui.addButton, &QPushButton::clicked, [this]() {
		std::string name = this->ui.nameLineEdit->text().toStdString();
		double price = this->ui.priceLineEdit->text().toDouble();
		this->serv.addProduct(name, price);
		this->populateList();
		this->ui.totalLineEdit->setText(QString::number(this->serv.getTotal()));
		});
}

ShoppingBasketWidget::~ShoppingBasketWidget()
{
}

void ShoppingBasketWidget::populateList()
{
	this->ui.productsListWidget->clear();

	for (Product p : this->serv.getAll())
		this->ui.productsListWidget->addItem(QString::fromStdString(p.toString()));
}

void ShoppingBasketWidget::update()
{
	this->populateList();
	this->ui.totalLineEdit->setText(QString::number(this->serv.getTotal()));
}
