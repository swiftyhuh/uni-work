#include "Service.h"

Service::Service(ShoppingBasket& basket) : basket{ basket } {}

void Service::addProduct(const std::string& name, double price) {
	Product p{ name, price };
	this->basket.addProduct(p);
	this->notify();
}

std::vector<Product> Service::getAll() {
	return this->basket.getAll();
}

int Service::getSize() const {
	return this->basket.getSize();
}

double Service::getTotal() const
{
	double total = 0;
	for (auto elem : this->basket.getAll())
		total += elem.getPrice();
	return total;
}
