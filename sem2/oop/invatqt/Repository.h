#pragma once
#include "Tutorial.h"
#include <string>
#include <vector>

/**
 * @brief In-memory storage layer for tutorials.
 */
class Repository {
private:
  std::vector<Tutorial> elems;
  /// @brief Finds index by unique identity (title + presenter).
  int find_pos(const std::string &title, const std::string &presenter) const;
  std::string filename;
  void load_from_file();
  void save_to_file();

public:
  Repository(const std::string &filename);
  /// @brief Adds tutorial if it does not already exist.
  /// @throws std::runtime_error on duplicate.
  void add_tutorial(const Tutorial &t);
  /// @brief Deletes tutorial by identity.
  /// @throws std::runtime_error if tutorial does not exist.
  void delete_tutorial(const std::string &title, const std::string &presenter);
  /// @brief Updates tutorial by identity.
  /// @throws std::runtime_error if tutorial does not exist.
  void update_tutorial(const Tutorial &t);

  /// @brief Returns repository size.
  int get_size() const;
  /// @brief Returns a copy of all tutorials.
  std::vector<Tutorial> get_all() const;
};
