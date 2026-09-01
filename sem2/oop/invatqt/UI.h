#pragma once

#include "Services.h"

class UI {
private:
  Services &service;

  void print_main_menu();
  void print_admin_menu();
  void print_user_menu();

  void run_admin_mode();
  void run_user_mode();

  void add_tutorial();
  void delete_tutorial();
  void update_tutorial();
  void list_tutorials();

  void browse_tutorials();
  void show_watch_list();
  void delete_from_watch_list();
  void open_watch_list();

public:
  UI(Services &service);
  void run();
};
