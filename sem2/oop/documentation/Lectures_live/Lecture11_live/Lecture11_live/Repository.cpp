#include "Repository.h"
#include <fstream>

using namespace std;

RepositoryException::RepositoryException(const std::string& message) : message{ message }
{
}

std::string RepositoryException::getMessage() const
{
	return this->message;
}

// ----------------------------------------------------------------------------------

Repository::Repository(const std::string& filename) : filename{ filename } 
{
	this->readFromFile();
}

void Repository::add(const Spaceship& spaceship)
{
	this->spaceships.push_back(spaceship);
	this->writeToFile();
}

std::vector<Spaceship> Repository::getAll() const
{
	return this->spaceships;
}

void Repository::readFromFile()
{
	ifstream f{ "Spaceships.csv" };
	if (!f.is_open())
		throw RepositoryException{ "File could not be opened for reading!" };

	Spaceship s{};
	while (f >> s)
	{
		this->spaceships.push_back(s);
	}

	f.close();
}

void Repository::writeToFile()
{
	ofstream f("Spaceships.csv");
	if (!f.is_open())
		throw RepositoryException{ "File could not be opened for writing!" };

	for (auto s : spaceships)
	{
		f << s;
	}

	f.close();
}