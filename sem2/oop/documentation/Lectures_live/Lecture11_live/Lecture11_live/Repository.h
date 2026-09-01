#pragma once
#include "Spaceship.h"
#include <string>
#include <vector>

class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	RepositoryException(const std::string& message);
	std::string getMessage() const;
};

// ----------------------------------------------------------------------------------

class Repository
{
private:
	std::string filename;
	std::vector<Spaceship> spaceships;

public:
	Repository(const std::string& filename);
	void add(const Spaceship& spaceship);
	std::vector<Spaceship> getAll() const;

private:
	void readFromFile();
	void writeToFile();
};

