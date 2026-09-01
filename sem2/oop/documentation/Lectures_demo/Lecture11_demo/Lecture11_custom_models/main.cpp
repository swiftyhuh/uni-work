#include "lecture11_demo_custom_models.h"
#include <QtWidgets/QApplication>
#include "GeneRepository.h"
#include "GeneService.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GeneRepository repo("genes.txt");
	GeneService serv{ repo };
	Lecture11_demo_custom_models w{ serv };
	w.show();
	return a.exec();
}
