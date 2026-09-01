#include "Service.h"

Service::Service(ShoppingBasket& basket) : basket{ basket } {}

void Service::addProduct(const std::string& name, double price) {
	Product p{ name, price };
	this->basket.addProduct(p);
}

std::vector<Product>& Service::getAll() {
	return this->basket.getAll();
}

int Service::getSize() const {
	return this->basket.getSize();
}

double Service::getTotal() const {
	double t = 0;
	for (Product p : this->basket.getAll())
		t += p.getPrice();
	return t;
}
