#include "Tutorial.h"
#include <sstream>
Duration::Duration(int min, int sec) : min(min), sec(sec) {}

int Duration::get_min() const { return min; }

int Duration::get_sec() const { return sec; }

Tutorial::Tutorial(const std::string &title, const std::string &presenter,
                   const Duration &duration, int likes, const std::string &link)
    : title(title), presenter(presenter), link(link), duration(duration),
      likes(likes) {}

std::string Tutorial::get_title() const { return title; }

std::string Tutorial::get_presenter() const { return presenter; }

Duration Tutorial::get_duration() const { return duration; }

int Tutorial::get_likes() const { return likes; }

std::string Tutorial::get_link() const { return link; }

std::ostream &operator<<(std::ostream &out, const Tutorial &tutorial) {
  out << "Title: " << tutorial.title << " | Presenter: " << tutorial.presenter
      << " | Duration: " << tutorial.duration.get_min() << ":";
  if (tutorial.duration.get_sec() < 10)
    out << "0";
  out << tutorial.duration.get_sec() << " | Likes: " << tutorial.likes
      << " | Link: " << tutorial.link;
  return out;
}

std::istream &operator>>(std::istream &in, Tutorial &tutorial) {
  std::string line;

  do {
    if (!std::getline(in, line))
      return in;
  } while (line.empty());

  std::stringstream ss(line);
  std::string title, presenter, min_str, sec_str, likes_str, link;

  std::getline(ss, title, ',');
  std::getline(ss, presenter, ',');
  std::getline(ss, min_str, ',');
  std::getline(ss, sec_str, ',');
  std::getline(ss, likes_str, ',');
  std::getline(ss, link);

  int min = std::stoi(min_str);
  int sec = std::stoi(sec_str);
  int likes = std::stoi(likes_str);

  tutorial = Tutorial(title, presenter, Duration(min, sec), likes, link);
  return in;
}
