#include "ui.h"

int main() {
  Person person("Mibu");
  person.addAnalysis(new BMI("2026.05.10", 32.4));
  person.addAnalysis(new BP("2026.05.11", 140, 90));

  UI ui(person);
  ui.run();
  return 0;
}
