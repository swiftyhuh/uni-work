#include "Observer_stub.h"
#include <QtWidgets/QApplication>
#include "Service.h"
#include "ShoppingBasketWidget.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	
	ShoppingBasket basket{};
	basket.addProduct(Product{ "Apples", 18 });
	basket.addProduct(Product{ "Butter", 16 });
	basket.addProduct(Product{ "Orange juice", 22 });
	basket.addProduct(Product{ "Surgical mask", 3 });

	Service serv{ basket };

	ShoppingBasketWidget w1{serv};
	ShoppingBasketWidget w2{serv};
	serv.addObserver(&w1);
	serv.addObserver(&w2);

	w1.show();
	w2.show();

	return a.exec();
}
