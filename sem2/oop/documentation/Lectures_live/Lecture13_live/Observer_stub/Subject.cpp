#include "Subject.h"

void Subject::addObserver(Observer* obs)
{
	this->observers.push_back(obs);
}

void Subject::notify() const
{
	for (Observer* obs : this->observers)
		obs->update();
}
