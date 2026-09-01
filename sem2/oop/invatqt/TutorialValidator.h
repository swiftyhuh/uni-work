#pragma once
#include <string>

class TutorialValidator {
public:
  void validate_tutorial(std::string title, std::string presenter, int min,
                         int sec, int likes, std::string link);

  void validate_identity(std::string title, std::string presenter);
};
