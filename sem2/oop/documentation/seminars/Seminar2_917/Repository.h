#pragma once
#include "DynmicArr.h"
#include "Song.h"

class Repository
{
private:
	DynamicArr storage;

public:
	void add(const Song &s);
	int getSize();
};

