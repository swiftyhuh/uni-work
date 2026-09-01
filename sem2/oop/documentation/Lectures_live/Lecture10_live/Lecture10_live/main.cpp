#include <QtWidgets/QApplication>
#include "GUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo{ "Spaceships.csv" };
    Service serv{ repo };
    GUI gui{ serv };
    gui.show();

    return a.exec();
}
