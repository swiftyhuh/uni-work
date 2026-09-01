#include "Song.h"

Duration::Duration(int min, int sec): min(min), sec(sec)
{}

Song::Song(const std::string& artist, const std::string& title, const Duration& duration, const std::string &youtube_link) :
	artist(artist), title(title), duration(duration),youtube_link(youtube_link)
{
}

std::string Song::get_artist() const {
	return artist;
}

std::string Song::get_title() const{
	return title;
}