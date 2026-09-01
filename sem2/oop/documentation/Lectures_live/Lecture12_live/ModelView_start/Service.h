#pragma once
#include "ShoppingBasket.h"

class Service
{
private:
	ShoppingBasket& basket;

public:
	Service(ShoppingBasket& basket);
	void addProduct(const std::string& name, double price);
	std::vector<Product>& getAll();
	int getSize() const;
	double getTotal() const;
};