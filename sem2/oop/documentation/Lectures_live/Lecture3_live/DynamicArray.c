#include "DynamicArray.h"
#include <stdlib.h>

DynamicArray* createArray(int cap, destroyFct op)
{
	DynamicArray* arr = malloc(sizeof(DynamicArray));
	if (arr == NULL)
		return NULL;

	arr->capacity = cap;
	arr->size = 0;
	arr->destructionOperation = op;

	arr->elems = malloc(sizeof(TElem) * cap);
	if (arr->elems == NULL)
	{
		free(arr);
		return NULL;
	}

	return arr;
}

void destroyDynamicArray(DynamicArray* arr)
{
	if (arr == NULL)
		return;

	for (int i = 0; i < arr->size; i++)
		arr->destructionOperation(arr->elems[i]);

	free(arr->elems);
	free(arr);
}

void resize(DynamicArray* arr) {
	if (arr == NULL)
		return;

	arr->capacity *= 2;
	/*TElem* aux = malloc(sizeof(TElem) * arr->capacity);
	for (int i = 0; i < arr->size; i++)
		aux[i] = arr->elems[i];

	free(arr->elems);
	arr->elems = aux;*/

	TElem* aux = realloc(arr->elems, arr->capacity * sizeof(TElem));
	if (aux == NULL)
		return;
	arr->elems = aux;
}

void add(DynamicArray* arr, TElem elem)
{
	if (arr == NULL)
		return;

	if (arr->size == arr->capacity)
		resize(arr);
	arr->elems[arr->size++] = elem;
}
