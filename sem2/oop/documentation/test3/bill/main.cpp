#include "Repository.h"
#include "Service.h"
#include "gui.h"
#include <QApplication>

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  Repository repo("bills.txt");
  Service service(repo);

  GUI gui(service);
  gui.show();

  return app.exec();
}
