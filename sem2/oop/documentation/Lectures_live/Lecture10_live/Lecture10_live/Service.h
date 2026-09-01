#pragma once
#include "Repository.h"

class Service
{
private:
	Repository& repo;

public:
	Service(Repository& repo);
	void add(const std::string& name, const std::string& type, const std::string& captain);
	std::vector<Spaceship> getAll() const;
};

