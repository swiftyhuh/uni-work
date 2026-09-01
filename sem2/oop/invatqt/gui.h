#pragma once

#include "Services.h"
#include "Tutorial.h"
#include <QWidget>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui {
class Form;
}
QT_END_NAMESPACE

class GUI : public QWidget {
  Q_OBJECT

public:
  GUI(Services &csv_service, Services &html_service, QWidget *parent = nullptr);
  ~GUI();

private:
  Ui::Form *ui;
  Services &csv_service;
  Services &html_service;
  Services *service;
  std::vector<Tutorial> filtered;
  int current_index;

  QString tutorial_to_qstring(Tutorial tutorial);
  void populate_admin_list();
  void populate_watch_list();
  void show_current_tutorial();
  void connect_signals();
};
