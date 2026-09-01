#include "Repository.h"
#include "Exceptions.h"
#include "Tutorial.h"
#include <algorithm>
#include <fstream>

Repository::Repository(const std::string &filename) : filename(filename) {
  this->load_from_file();
}

int Repository::find_pos(const std::string &title,
                         const std::string &presenter) const {
  auto it = std::find_if(this->elems.begin(), this->elems.end(),
                         [&](const Tutorial &tutorial) {
                           return tutorial.get_title() == title &&
                                  tutorial.get_presenter() == presenter;
                         });

  if (it == this->elems.end())
    return -1;

  return it - this->elems.begin();
}

void Repository::load_from_file() {
  this->elems.clear();

  std::ifstream file(this->filename);
  if (!file.is_open())
    return;

  Tutorial tutorial;
  while (file >> tutorial)
    this->elems.push_back(tutorial);

  file.close();
}

void Repository::save_to_file() {
  std::ofstream file(this->filename);
  if (!file.is_open())
    return;

  for (const auto &tutorial : this->elems) {
    Duration d = tutorial.get_duration();
    file << tutorial.get_title() << "," << tutorial.get_presenter() << ","
         << d.get_min() << "," << d.get_sec() << "," << tutorial.get_likes()
         << "," << tutorial.get_link() << "\n";
  }

  file.close();
}

void Repository::add_tutorial(const Tutorial &t) {
  if (find_pos(t.get_title(), t.get_presenter()) != -1) {
    throw RepositoryException("Tutorial already exists.");
  }
  this->elems.push_back(t);
  this->save_to_file();
}

void Repository::delete_tutorial(const std::string &title,
                                 const std::string &presenter) {
  int pos = find_pos(title, presenter);
  if (pos == -1) {
    throw RepositoryException("Tutorial does not exist.");
  }
  this->elems.erase(elems.begin() + pos);
  this->save_to_file();
}

void Repository::update_tutorial(const Tutorial &t) {
  int pos = find_pos(t.get_title(), t.get_presenter());
  if (pos == -1) {
    throw RepositoryException("Tutorial does not exist.");
  }
  this->elems[pos] = t;
  this->save_to_file();
}

int Repository::get_size() const { return this->elems.size(); }

std::vector<Tutorial> Repository::get_all() const { return this->elems; }
