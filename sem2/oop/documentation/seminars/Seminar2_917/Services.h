#pragma once
#include "Repository.h"

class Services
{
	Repository& repo;
public:
	void add(std::string title, std::string artist, int min, int sec, std::string link);
	int getSize();
	Services(Repository& repo);
};

