#include "DynamicArray.h"
#include <crtdbg.h>

int main() {
	Planet* p1 = createPlanet("Wolf 1061 c", "terrestrial", 13.8);
	Planet* p2 = createPlanet("HAT-P-26b", "Neptune-like", 450);
	Planet* p3 = createPlanet("Proxima Centauri b", "terrestrial", 4.2);

	DynamicArray* arr = createArray(2, &destroyPlanet);
	add(arr, p1);
	add(arr, p2);
	add(arr, p3);
	// destroyDynamicArray(arr);

	DynamicArray* arrayOfArrays = createArray(2, &destroyDynamicArray);
	add(arrayOfArrays, arr);
	destroyDynamicArray(arrayOfArrays);

	_CrtDumpMemoryLeaks();
	return 0;
}