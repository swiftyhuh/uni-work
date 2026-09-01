#include <QtWidgets/QApplication>
#include "Service.h"
#include "GUI.h"
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    ShoppingBasket basket{};
    Service serv{ basket };
    serv.addProduct("Apples", 18 );
    serv.addProduct("Butter", 16 );
    serv.addProduct("Orange juice", 22 );
    serv.addProduct("Surgical mask", 3 );

    std::unique_ptr<MyModel> model = std::make_unique<MyModel>(serv);
    GUI gui{ model.get() };
    gui.show();

    GUI gui2{ model.get() };
    gui2.show();
   
    return a.exec();
}
