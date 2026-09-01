#include "Repository.h"
#include "Services.h"

void Repository::add(const Song& s)
{
	this->storage.addElem(s);
}

int Repository::getSize()
{
	return this->storage.getSize();
}
