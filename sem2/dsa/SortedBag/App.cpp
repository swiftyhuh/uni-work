#include "ExtendedTest.h"
#include "ShortTest.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

using namespace std;

int main() {
  testAll();
  testAllExtended();

  cout << "Test over" << endl;
  system("pause");
}
