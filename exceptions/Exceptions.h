#pragma once
#include <string>
#include <exception>

class FileException : public std::exception {
private:
	std::string message;
public:
	FileException(const std::string& message);
	virtual const char* what();
};

class RepositoryException : public std::exception {
private:
	std::string message;
public:
	RepositoryException();
	RepositoryException(const std::string& message);
	virtual ~RepositoryException();
	virtual const char* what();
};

class DuplicateEventException : public RepositoryException {
public:
	const char* what();
};

class InvalidPositionException : public RepositoryException {
public:
	const char* what();
};

class EventNonExistentException : public RepositoryException {
public:
	const char* what();
};

class BrowserError : public std::exception {
public:
	const char* what();
};
