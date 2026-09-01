#include "Services.h"

void Services::add(std::string title, std::string artist, int min, int sec, std::string link) {
	Duration d{ min, sec };
	Song s{ title, artist, d, link };
	this->repo.add(s);
}

int Services::getSize() {
	return this->repo.getSize();
}

Services::Services(Repository& repo): repo{repo}
{
}
