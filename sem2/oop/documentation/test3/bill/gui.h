#pragma once
#include "Service.h"
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class GUI : public QWidget {
  Q_OBJECT

public:
  GUI(Service &service, QWidget *parent = nullptr);
  ~GUI();

private:
  Ui::Form *ui;
  Service &service;
  void populateList();
  void connectSignals();
};
