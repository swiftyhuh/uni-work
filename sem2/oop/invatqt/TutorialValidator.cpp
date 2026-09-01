#include "TutorialValidator.h"
#include "Exceptions.h"
void TutorialValidator::validate_tutorial(std::string title,
                                          std::string presenter, int min,
                                          int sec, int likes,
                                          std::string link) {
  if (title.empty())
    throw ValidationException("Title cannot be empty.");
  if (presenter.empty())
    throw ValidationException("Title cannot be empty.");
  if (link.empty())
    throw ValidationException("Link cannot be empty.");
  if (min < 0 || min > 60)
    throw ValidationException("Minutes must be between 0 and 60.");
  if (sec < 0 || sec > 60)
    throw ValidationException("Seconds must be between 0 and 60.");
  if (likes <= 0)
    throw ValidationException("Likes must be greater than 0.");
}

void TutorialValidator::validate_identity(std::string title,
                                          std::string presenter) {
  if (title.empty() || presenter.empty())
    throw ValidationException("Title and presenter cannot be empty.");
}
