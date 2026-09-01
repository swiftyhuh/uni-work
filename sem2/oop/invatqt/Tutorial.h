#pragma once
#include <iostream>
#include <string>

/**
 * @brief Stores a tutorial duration in minutes and seconds.
 */
class Duration {
private:
  int min, sec;

public:
  /// @brief Builds a duration object.
  /// @param min Minutes component.
  /// @param sec Seconds component.
  Duration(int min = 0, int sec = 0);

  /// @brief Returns minutes.
  int get_min() const;
  /// @brief Returns seconds.
  int get_sec() const;
};

/**
 * @brief Represents one tutorial entity from the repository.
 */
class Tutorial {
private:
  std::string title, presenter, link;
  Duration duration;
  int likes;

public:
  /// @brief Builds a tutorial object.
  /// @param title Tutorial title.
  /// @param presenter Tutorial presenter.
  /// @param duration Tutorial duration.
  /// @param likes Number of likes.
  /// @param link Tutorial link.
  Tutorial(const std::string &title = "", const std::string &presenter = "",
           const Duration &duration = Duration{}, int likes = 0,
           const std::string &link = "");
  /// @brief Returns tutorial title.
  std::string get_title() const;
  /// @brief Returns tutorial presenter.
  std::string get_presenter() const;
  /// @brief Returns tutorial duration.
  Duration get_duration() const;
  /// @brief Returns number of likes.
  int get_likes() const;
  /// @brief Returns tutorial link.
  std::string get_link() const;

  friend std::ostream &operator<<(std::ostream &out, const Tutorial &tutorial);
  friend std::istream &operator>>(std::istream &in, Tutorial &tutorial);
};
