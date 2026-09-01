#pragma once
#include "Planet.h"

typedef void* TElem;

typedef void (*destroyFct)(TElem);

typedef struct {
	int capacity, size;
	TElem* elems;
	destroyFct destructionOperation;
} DynamicArray;

DynamicArray* createArray(int cap, destroyFct op);
void destroyDynamicArray(DynamicArray* arr);
void add(DynamicArray* arr, TElem elem);
