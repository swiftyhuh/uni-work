#pragma once

#include "Repository.h"
#include "TutorialValidator.h"
#include "WatchList.h"
#include <string>
#include <vector>

/**
 * @brief Service layer for tutorial business operations and validation.
 */
class Services {
private:
  Repository &repo;
  TutorialValidator validator;
  WatchList *watch_list;
  int find_in_watch_list(const std::string &title,
                         const std::string &presenter) const;

public:
  /// @brief Builds services over a repository instance.
  Services(Repository &repo, WatchList *watch_list);

  /// @brief Validates and adds a tutorial.
  void add_tutorial(const std::string &title, const std::string &presenter,
                    int min, int sec, int likes, const std::string &link);
  /// @brief Validates identity and deletes a tutorial.
  void delete_tutorial(const std::string &title, const std::string &presenter);
  /// @brief Validates and updates a tutorial.
  void update_tutorial(const std::string &title, const std::string &presenter,
                       int min, int sec, int likes, const std::string &link);

  /// @brief Returns number of tutorials.
  int get_size() const;
  /// @brief Returns all tutorials.
  std::vector<Tutorial> get_all() const;

  std::vector<Tutorial>
  get_tutorial_by_presenter(const std::string &presenter) const;
  void add_to_watchlist(const Tutorial &tutorial);
  std::vector<Tutorial> get_watchlist() const;
  void delete_from_watch_list(const std::string &title,
                              const std::string &presenter, bool like);
  void display_watchlist();
};
