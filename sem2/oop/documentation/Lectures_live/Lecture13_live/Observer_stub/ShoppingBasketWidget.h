#pragma once

#include <QWidget>
#include "ui_ShoppingBasketWidget.h"
#include "Service.h"
#include "Observer.h"

class ShoppingBasketWidget : public QWidget, public Observer
{
	Q_OBJECT

public:
	ShoppingBasketWidget(Service& serv, QWidget *parent = Q_NULLPTR);
	~ShoppingBasketWidget();

private:
	Ui::ShoppingBasketWidget ui;
	Service& serv;

public:
	void populateList();
	void update() override;
};
