#include "DynmicArr.h"

DynamicArr::DynamicArr(int capacity) {
	data = new TElem[capacity];
	this->capacity = capacity;
	size = 0;
}

DynamicArr::~DynamicArr()
{
	delete[] data;
}

DynamicArr::DynamicArr(const DynamicArr& arr) {
	capacity = arr.capacity;
	size = arr.size;
	data = new TElem[capacity];
	for (int i = 0; i < size; i++) {
		data[i] = arr.data[i];
	}
}

void DynamicArr::resize(float capMultiplier) {
	this->capacity *= capMultiplier;
	TElem* newData = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) {
		newData[i] = this->data[i];
	}
	delete[] this->data;
	this->data = newData;
}

void DynamicArr::addElem(TElem elem) {
	if (this->size == this->capacity) {
		resize();
	}
	this->data[this->size++] = elem;
}
int DynamicArr::getSize() const {
	return this->size;
}
DynamicArr& DynamicArr::operator=(const DynamicArr& other) {
	if (this == &other)
		return *this;

	this->capacity = other.capacity;
	this->size = other.size;
	delete[] this->data;
	this->data = new TElem[this->capacity];
	for (int i = 0; i < this->size; i++) {
		this->data[i] = other.data[i];
	}
	return *this;
}