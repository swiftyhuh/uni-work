#pragma once
#include "Song.h"

typedef Song TElem;

class DynamicArr
{
private:
	TElem* data;
	int size;
	int capacity;
	void resize(float capMultiplier = 2);
public:
	DynamicArr(int capacity=2);
	~DynamicArr();
	void addElem(TElem elem);
	DynamicArr(const DynamicArr& arr);
	int getSize() const;
	DynamicArr& operator=(const DynamicArr& other);
};

