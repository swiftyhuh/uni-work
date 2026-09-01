#include "Service.h"

Service::Service(Repository& repo): repo{repo}
{
}

void Service::add(const std::string& name, const std::string& type, const std::string& captain)
{
	Spaceship s{ name, type, captain };
	this->repo.add(s);
}

std::vector<Spaceship> Service::getAll() const
{
	return this->repo.getAll();
}
