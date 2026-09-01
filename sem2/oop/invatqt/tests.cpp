#include "tests.h"
#include "Exceptions.h"
#include "Repository.h"
#include "Services.h"
#include "Tutorial.h"
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

Tutorial make_tutorial(std::string title, std::string presenter, int min,
                       int sec, int likes, std::string link) {
  return Tutorial(title, presenter, Duration(min, sec), likes, link);
}

void reset_file(std::string file_name) {
  std::ofstream file(file_name);
  file.close();
}

void test_tutorial_and_duration() {
  Duration d(3, 45);
  assert(d.get_min() == 3);
  assert(d.get_sec() == 45);

  Tutorial t("OOP", "Alice", d, 120, "https://oop");
  assert(t.get_title() == "OOP");
  assert(t.get_presenter() == "Alice");
  assert(t.get_duration().get_min() == 3);
  assert(t.get_duration().get_sec() == 45);
  assert(t.get_likes() == 120);
  assert(t.get_link() == "https://oop");
}

void test_repository() {
  reset_file("test_repo.txt");
  Repository repo("test_repo.txt");

  Tutorial t1 = make_tutorial("Cpp", "Bob", 10, 0, 100, "l1");
  Tutorial t2 = make_tutorial("STL", "Dan", 12, 5, 200, "l2");

  repo.add_tutorial(t1);
  assert(repo.get_size() == 1);

  bool threw = false;
  try {
    repo.add_tutorial(make_tutorial("Cpp", "Bob", 11, 0, 150, "l3"));
  } catch (RepositoryException &) {
    threw = true;
  }
  assert(threw);

  repo.add_tutorial(t2);
  assert(repo.get_size() == 2);

  repo.update_tutorial(make_tutorial("Cpp", "Bob", 20, 10, 999, "updated"));
  std::vector<Tutorial> all = repo.get_all();
  assert(all.size() == 2);
  assert(all[0].get_likes() == 999);
  assert(all[0].get_link() == "updated");

  threw = false;
  try {
    repo.update_tutorial(make_tutorial("Missing", "Nobody", 1, 1, 1, "x"));
  } catch (RepositoryException &) {
    threw = true;
  }
  assert(threw);

  repo.delete_tutorial("STL", "Dan");
  assert(repo.get_size() == 1);

  threw = false;
  try {
    repo.delete_tutorial("STL", "Dan");
  } catch (RepositoryException &) {
    threw = true;
  }
  assert(threw);
}

void test_services() {
  reset_file("test_repo.txt");
  reset_file("test_watchlist.csv");

  Repository repo("test_repo.txt");
  CSVWatchList watch_list("test_watchlist.csv");
  Services service(repo, &watch_list);

  service.add_tutorial("Basics", "Mike", 9, 59, 10, "link");
  assert(service.get_size() == 1);

  bool threw_validation = false;
  try {
    service.add_tutorial("", "Mike", 9, 10, 5, "link");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  threw_validation = false;
  try {
    service.add_tutorial("BadSec", "Mike", 9, 70, 5, "link");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  threw_validation = false;
  try {
    service.add_tutorial("BadMin", "Mike", -1, 10, 5, "link");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  threw_validation = false;
  try {
    service.add_tutorial("BadPresenter", "", 9, 10, 5, "link");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  threw_validation = false;
  try {
    service.add_tutorial("BadLink", "Mike", 9, 10, 5, "");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  threw_validation = false;
  try {
    service.add_tutorial("BadLikes", "Mike", 9, 10, 0, "link");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);

  bool threw_repo = false;
  try {
    service.add_tutorial("Basics", "Mike", 9, 59, 10, "link2");
  } catch (RepositoryException &) {
    threw_repo = true;
  }
  assert(threw_repo);

  service.update_tutorial("Basics", "Mike", 10, 0, 99, "new_link");
  std::vector<Tutorial> all = service.get_all();
  assert(all.size() == 1);
  assert(all[0].get_likes() == 99);
  assert(all[0].get_link() == "new_link");

  service.delete_tutorial("Basics", "Mike");
  assert(service.get_size() == 0);

  threw_repo = false;
  try {
    service.delete_tutorial("Basics", "Mike");
  } catch (RepositoryException &) {
    threw_repo = true;
  }
  assert(threw_repo);

  threw_validation = false;
  try {
    service.delete_tutorial("", "Mike");
  } catch (ValidationException &) {
    threw_validation = true;
  }
  assert(threw_validation);
}

void test_user_mode_services() {
  reset_file("test_repo.txt");
  reset_file("test_watchlist.csv");

  Repository repo("test_repo.txt");
  CSVWatchList watch_list("test_watchlist.csv");
  Services service(repo, &watch_list);

  service.add_tutorial("C++ Basics", "Bjarne", 10, 10, 100, "l1");
  service.add_tutorial("OOP Basics", "Bjarne", 12, 20, 150, "l2");
  service.add_tutorial("Templates", "Scott", 14, 30, 200, "l3");

  std::vector<Tutorial> all = service.get_tutorial_by_presenter("");
  assert(all.size() == 3);

  std::vector<Tutorial> by_presenter =
      service.get_tutorial_by_presenter("Bjarne");
  assert(by_presenter.size() == 2);
  assert(by_presenter[0].get_presenter() == "Bjarne");
  assert(by_presenter[1].get_presenter() == "Bjarne");

  std::vector<Tutorial> missing = service.get_tutorial_by_presenter("Nobody");
  assert(missing.size() == 0);

  service.add_to_watchlist(by_presenter[0]);
  assert(service.get_watchlist().size() == 1);

  bool threw_repo = false;
  try {
    service.add_to_watchlist(by_presenter[0]);
  } catch (RepositoryException &) {
    threw_repo = true;
  }
  assert(threw_repo);

  service.delete_from_watch_list(by_presenter[0].get_title(),
                                 by_presenter[0].get_presenter(), false);
  assert(service.get_watchlist().size() == 0);

  threw_repo = false;
  try {
    service.delete_from_watch_list("Missing", "Nobody", false);
  } catch (RepositoryException &) {
    threw_repo = true;
  }
  assert(threw_repo);

  Tutorial liked = by_presenter[1];
  service.add_to_watchlist(liked);
  int old_likes = liked.get_likes();
  service.delete_from_watch_list(liked.get_title(), liked.get_presenter(),
                                 true);

  std::vector<Tutorial> updated = service.get_tutorial_by_presenter("Bjarne");
  bool found_updated = false;

  for (auto tutorial : updated) {
    if (tutorial.get_title() == liked.get_title() &&
        tutorial.get_presenter() == liked.get_presenter()) {
      assert(tutorial.get_likes() == old_likes + 1);
      found_updated = true;
    }
  }

  assert(found_updated);
}

void run_all_tests() {
  test_tutorial_and_duration();
  test_repository();
  test_services();
  test_user_mode_services();

  std::cout << "All tests passed.\n";
}
