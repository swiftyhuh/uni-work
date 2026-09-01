#pragma once
#include <exception>
#include <string>

class RepositoryException : public std::exception {
private:
  std::string message;

public:
  RepositoryException(std::string msg) : message(msg) {}
  const char *what() const noexcept override { return message.c_str(); }
  // overrides the standard what() method to return the error message
};

class ValidationException : public std::exception {
private:
  std::string message;

public:
  ValidationException(std::string msg) : message(msg) {}
  const char *what() const noexcept override { return message.c_str(); }
};
