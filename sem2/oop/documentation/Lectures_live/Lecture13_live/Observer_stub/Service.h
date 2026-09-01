#pragma once
#include "ShoppingBasket.h"
#include "Subject.h"

class Service: public Subject
{
private:
	ShoppingBasket& basket;

public:
	Service(ShoppingBasket& basket);
	void addProduct(const std::string& name, double price);
	std::vector<Product> getAll();
	int getSize() const;
	double getTotal() const;
};