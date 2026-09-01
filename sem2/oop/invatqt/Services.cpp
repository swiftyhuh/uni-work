#include "Services.h"
#include "Exceptions.h"
#include "Tutorial.h"
#include "WatchList.h"
#include <algorithm>

Services::Services(Repository &repo, WatchList *watch_list)
    : repo(repo), watch_list(watch_list) {}

void Services::add_tutorial(const std::string &title,
                            const std::string &presenter, int min, int sec,
                            int likes, const std::string &link) {
  this->validator.validate_tutorial(title, presenter, min, sec, likes, link);
  Duration d(min, sec);
  Tutorial t(title, presenter, d, likes, link);
  this->repo.add_tutorial(t);
}

void Services::delete_tutorial(const std::string &title,
                               const std::string &presenter) {
  this->validator.validate_identity(title, presenter);
  this->repo.delete_tutorial(title, presenter);
}

void Services::update_tutorial(const std::string &title,
                               const std::string &presenter, int min, int sec,
                               int likes, const std::string &link) {
  this->validator.validate_tutorial(title, presenter, min, sec, likes, link);
  Duration d(min, sec);
  Tutorial t(title, presenter, d, likes, link);
  this->repo.update_tutorial(t);
}

int Services::get_size() const { return this->repo.get_size(); }

std::vector<Tutorial> Services::get_all() const { return repo.get_all(); }

int Services::find_in_watch_list(const std::string &title,
                                 const std::string &presenter) const {
  std::vector<Tutorial> tutorials = this->watch_list->get_all();
  auto it = std::find_if(tutorials.begin(), tutorials.end(),
                         [&](const Tutorial &tutorial) {
                           return tutorial.get_title() == title &&
                                  tutorial.get_presenter() == presenter;
                         });
  if (it == tutorials.end())
    return -1;

  return it - tutorials.begin();
}

std::vector<Tutorial>
Services::get_tutorial_by_presenter(const std::string &presenter) const {
  std::vector<Tutorial> result;
  std::vector<Tutorial> all = repo.get_all();

  for (const auto &tutorial : all) {
    if (presenter.empty() || tutorial.get_presenter() == presenter)
      result.push_back(tutorial);
  }
  return result;
}

void Services::add_to_watchlist(const Tutorial &tutorial) {
  if (find_in_watch_list(tutorial.get_title(), tutorial.get_presenter()) != -1)
    throw RepositoryException("Tutorial already exists in watch list.");
  this->watch_list->add(tutorial);
  this->watch_list->write_to_file();
}

std::vector<Tutorial> Services::get_watchlist() const {
  return this->watch_list->get_all();
}

void Services::delete_from_watch_list(const std::string &title,
                                      const std::string &presenter, bool like) {
  int pos = find_in_watch_list(title, presenter);
  if (pos == -1)
    throw RepositoryException("Tutorial does not exist in watch list.");
  std::vector<Tutorial> tutorials = this->watch_list->get_all();
  Tutorial tutorial = tutorials[pos];
  this->watch_list->remove(title, presenter);
  this->watch_list->write_to_file();
  if (like) {
    Duration d = tutorial.get_duration();
    Tutorial update(tutorial.get_title(), tutorial.get_presenter(), d,
                    tutorial.get_likes() + 1, tutorial.get_link());
    this->repo.update_tutorial(update);
  }
}

void Services::display_watchlist() { this->watch_list->display(); }
