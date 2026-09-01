#include "WatchList.h"
#include "Exceptions.h"
#include "Tutorial.h"
#include <algorithm>
#include <fstream>

WatchList::WatchList(std::string filename) { this->filename = filename; }

void WatchList::add(Tutorial tutorial) { this->tutorials.push_back(tutorial); }

void WatchList::remove(std::string title, std::string presenter) {
  auto it = std::find_if(this->tutorials.begin(), this->tutorials.end(),
                         [&](Tutorial tutorial) {
                           return tutorial.get_title() == title &&
                                  tutorial.get_presenter() == presenter;
                         });
  if (it == this->tutorials.end())
    throw RepositoryException("Tutorial does not exist in watch list.");

  this->tutorials.erase(it);
}

std::vector<Tutorial> WatchList::get_all() { return this->tutorials; }

CSVWatchList::CSVWatchList(std::string filename) : WatchList(filename) {}

void CSVWatchList::write_to_file() {
  std::ofstream file(this->filename);
  for (auto tutorial : this->tutorials) {
    Duration d = tutorial.get_duration();
    file << tutorial.get_title() << "," << tutorial.get_presenter() << ","
         << d.get_min() << "," << d.get_sec() << "," << tutorial.get_likes()
         << "," << tutorial.get_link() << "\n";
  }
  file.close();
}

void CSVWatchList::display() {
  std::string command = "xdg-open \"" + this->filename + "\"";
  system(command.c_str());
}

HTMLWatchList::HTMLWatchList(std::string filename) : WatchList(filename) {}

void HTMLWatchList::write_to_file() {
  std::ofstream file(this->filename);

  file << "<!DOCTYPE html>\n";
  file << "<html>\n";
  file << "<head>\n";
  file << "<title>Watch List</title>\n";
  file << "</head>\n";
  file << "<body>\n";
  file << "<table border=\"1\">\n";
  file << "<tr>\n";
  file << "<td>Title</td>\n";
  file << "<td>Presenter</td>\n";
  file << "<td>Minutes</td>\n";
  file << "<td>Seconds</td>\n";
  file << "<td>Likes</td>\n";
  file << "<td>Link</td>\n";
  file << "</tr>\n";

  for (auto tutorial : this->tutorials) {
    Duration d = tutorial.get_duration();

    file << "<tr>\n";
    file << "<td>" << tutorial.get_title() << "</td>\n";
    file << "<td>" << tutorial.get_presenter() << "</td>\n";
    file << "<td>" << d.get_min() << "</td>\n";
    file << "<td>" << d.get_sec() << "</td>\n";
    file << "<td>" << tutorial.get_likes() << "</td>\n";
    file << "<td><a href=\"" << tutorial.get_link() << "\">Link</a></td>\n";
    file << "</tr>\n";
  }

  file << "</table>\n";
  file << "</body>\n";
  file << "</html>\n";

  file.close();
}

void HTMLWatchList::display() {
  std::string command = "xdg-open \"" + this->filename + "\"";
  system(command.c_str());
}
