#include "UI.h"
#include "Exceptions.h"
#include "Tutorial.h"
#include <iostream>
#include <string>

UI::UI(Services &service) : service(service) {}

void UI::print_main_menu() {
  std::cout << "\n=== Master C++ ===\n1. Admin mode\n2. User mode\n0. Exit\n >";
}

void UI::print_admin_menu() {
  std::cout << "\n=== Admin Mode ===\n1. Add tutorial\n2. Delete tutorial\n3. "
               "Update tutorial\n4. List tutorials\n0. Exit\n >";
}

void UI::print_user_menu() {
  std::cout
      << "\n=== User Mode ===\n1. Browse tutorials\n2. Show watch "
         "list\n3. Delete from watch list\n4. Open watch list file\n0. Back\n";
}

void UI::open_watch_list() { this->service.display_watchlist(); }

void UI::add_tutorial() {
  std::string title, presenter, link, text;
  int min = -1, sec = -1, likes = 0;

  std::cout << "Title: ";
  std::getline(std::cin, title);
  std::cout << "Presenter: ";
  std::getline(std::cin, presenter);
  try {
    std::cout << "Minutes: ";
    std::getline(std::cin, text);
    min = std::stoi(text);

    std::cout << "Seconds: ";
    std::getline(std::cin, text);
    sec = std::stoi(text);

    std::cout << "Likes: ";
    std::getline(std::cin, text);
    likes = std::stoi(text);
  } catch (...) {
    throw ValidationException("Invalid input.");
  }
  std::cout << "Link: ";
  std::getline(std::cin, link);

  service.add_tutorial(title, presenter, min, sec, likes, link);
  std::cout << "Tutorial added.\n";
}

void UI::delete_tutorial() {
  std::string title, presenter;

  std::cout << "Title: ";
  std::getline(std::cin, title);
  std::cout << "Presenter: ";
  std::getline(std::cin, presenter);

  service.delete_tutorial(title, presenter);
  std::cout << "Tutorial deleted.\n";
}

void UI::update_tutorial() {
  std::string title, presenter, link, text;
  int min = -1, sec = -1, likes = 0;

  std::cout << "Title: ";
  std::getline(std::cin, title);
  std::cout << "Presenter: ";
  std::getline(std::cin, presenter);
  try {
    std::cout << "New minutes: ";
    std::getline(std::cin, text);
    min = std::stoi(text);

    std::cout << "New seconds: ";
    std::getline(std::cin, text);
    sec = std::stoi(text);

    std::cout << "New likes: ";
    std::getline(std::cin, text);
    likes = std::stoi(text);
  } catch (...) {
    throw ValidationException("Invalid input.");
  }
  std::cout << "New link: ";
  std::getline(std::cin, link);

  service.update_tutorial(title, presenter, min, sec, likes, link);
  std::cout << "Tutorial updated.\n";
}

void UI::list_tutorials() {
  std::vector<Tutorial> all = service.get_all();
  if (all.size() == 0) {
    std::cout << "No tutorials in repository.\n";
    return;
  }

  int index = 1;
  for (const auto &tutorial : all) {
    std::cout << index << ". " << tutorial << "\n";
    index++;
  }
}

void UI::browse_tutorials() {
  std::string presenter;
  std::cout << "Presenter (leave empty for all): ";
  std::getline(std::cin, presenter);

  std::vector<Tutorial> tutorials =
      service.get_tutorial_by_presenter(presenter);
  if (tutorials.size() == 0) {
    std::cout << "No tutorials found.\n";
    return;
  }
  int current = 0;
  bool running = true;

  while (running) {
    Tutorial tutorial = tutorials[current];
    Duration d = tutorial.get_duration();
    std::cout << "\nCurrent tutorial:\n";
    std::cout << "Title: " << tutorial.get_title() << "\n";
    std::cout << "Presenter: " << tutorial.get_presenter() << "\n";
    std::cout << "Duration: " << d.get_min() << ":";
    if (d.get_sec() < 10)
      std::cout << "0";
    std::cout << d.get_sec() << "\n";
    std::cout << "Likes: " << tutorial.get_likes() << "\n";
    std::cout << "Link: " << tutorial.get_link() << "\n";

    std::cout << "\n1. Add to watch list\n";
    std::cout << "2. Next\n";
    std::cout << "3. Play in browser\n";
    std::cout << "0. Stop\n";
    std::cout << "Choice: ";
    std::string text;
    int choice;

    try {
      std::getline(std::cin, text);
      choice = std::stoi(text);
    } catch (...) {
      throw ValidationException("Invalid input.");
    }

    try {
      if (choice == 1) {
        service.add_to_watchlist(tutorial);
        std::cout << "Tutorial added to watch list.\n";
        current++;
        if (current == tutorials.size())
          current = 0;
      } else if (choice == 2) {
        current++;
        if (current == tutorials.size())
          current = 0;
      } else if (choice == 3) {
        std::string command = "xdg-open \"" + tutorial.get_link() + "\"";
        system(command.c_str());
      } else if (choice == 0)
        running = false;
      else
        std::cout << "Invalid choice.\n";
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
}

void UI::show_watch_list() {
  std::vector<Tutorial> watch_list = service.get_watchlist();

  if (watch_list.size() == 0) {
    std::cout << "Watch list is empty.\n";
    return;
  }

  int index = 1;
  for (const auto &tutorial : watch_list) {
    std::cout << index << ". " << tutorial << "\n";
    index++;
  }
}

void UI::delete_from_watch_list() {
  std::string title, presenter, likes;

  std::cout << "Title: ";
  std::getline(std::cin, title);
  std::cout << "Presenter: ";
  std::getline(std::cin, presenter);
  std::cout << "Like tutorial? (1 for yes, 0 for no): ";
  int like;
  try {
    std::getline(std::cin, likes);
    like = std::stoi(likes);
  } catch (...) {
    throw ValidationException("Invalid input.");
  }

  service.delete_from_watch_list(title, presenter, like == 1);
  std::cout << "Tutorial deleted from watch list.\n";
}

void UI::run_admin_mode() {
  int choice;
  bool running = true;

  while (running) {
    print_admin_menu();

    try {
      std::string text;
      std::getline(std::cin, text);
      choice = std::stoi(text);
    } catch (...) {
      std::cout << "Error: Invalid input.\n";
      continue;
    }

    try {
      switch (choice) {
      case 1:
        add_tutorial();
        break;
      case 2:
        delete_tutorial();
        break;
      case 3:
        update_tutorial();
        break;
      case 4:
        list_tutorials();
        break;
      case 0:
        running = false;
        break;
      default:
        std::cout << "Invalid choice.\n";
        break;
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
}

void UI::run_user_mode() {
  int choice;
  bool running = true;

  while (running) {
    print_user_menu();

    try {
      std::string text;
      std::getline(std::cin, text);
      choice = std::stoi(text);
    } catch (...) {
      std::cout << "Error: Invalid input.\n";
      continue;
    }

    try {
      switch (choice) {
      case 1:
        browse_tutorials();
        break;
      case 2:
        show_watch_list();
        break;
      case 3:
        delete_from_watch_list();
        break;
      case 4:
        open_watch_list();
        break;
      case 0:
        running = false;
        break;
      default:
        std::cout << "Invalid choice.\n";
        break;
      }
    } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << "\n";
    }
  }
}

void UI::run() {
  int choice;
  bool running = true;

  while (running) {
    print_main_menu();

    try {
      std::string text;
      std::getline(std::cin, text);
      choice = std::stoi(text);
    } catch (...) {
      std::cout << "Error: Invalid input.\n";
      continue;
    }

    switch (choice) {
    case 1:
      run_admin_mode();
      break;
    case 2:
      run_user_mode();
      break;
    case 0:
      running = false;
      break;
    default:
      std::cout << "Invalid choice.\n";
      break;
    }
  }
}
