#include "Exceptions.h"

FileException::FileException(const std::string& message) {
	this->message = message;
}

const char* FileException::what() {
	return this->message.c_str();
}

RepositoryException::RepositoryException() {}

RepositoryException::RepositoryException(const std::string& message) {
	this->message = message;
}

RepositoryException::~RepositoryException() {}

const char* RepositoryException::what() {
	return this->message.c_str();
}

const char* DuplicateEventException::what() {
	return "The event is already in the repository";
}

const char* InvalidPositionException::what() {
	return "Invalid Position!";
}

const char* EventNonExistentException::what() {
	return "No such event in repository!";
}

const char* BrowserError::what() {
	return "The event cannot be opened!";
}