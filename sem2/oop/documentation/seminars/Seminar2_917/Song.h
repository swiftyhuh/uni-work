#pragma once

#include <string>
class Duration {
private:
	int min;
	int sec;
public:
	Duration(int min = 0, int sec = 0);
};

class Song
{
private:
	std::string artist;
	std::string title;
	Duration duration;
	std::string youtube_link;
public:
	Song(const std::string &artist = "", const std::string& title = "", const Duration& duration = {}, const std::string& youtube_link = "");
	std::string get_artist() const;
	std::string get_title() const;
};

