#include "FileRepository.h"
#include "exceptions/Exceptions.h"
#include "validator/EventValidator.h"
#include <filesystem>
#include <fstream>
FileRepository::~FileRepository() {
	this->saveToFile();
}

void FileRepository::addEventToRepository(const Event& e) {
	Repository::addEventToRepository(e);
	this->saveToFile();
}

void FileRepository::removeEventFromRepository(int position) {
	Repository::removeEventFromRepository(position);
	this->saveToFile();
}

void FileRepository::updateEventInRepository(int position, const Event& new_event) {
	Repository::updateEventInRepository(position, new_event);
	this->saveToFile();
}

void FileRepository::readFromFile() {
	std::filesystem::path p = std::filesystem::current_path();
	//std::ifstream is(this->file_path);
	std::filesystem::path path = std::filesystem::absolute(this->file_path);
	while (path.filename() != "Events-Manager") path = path.parent_path();
	path /= "data";
	path /= "Events.txt";

	std::ifstream is(path);

	if (is.is_open() == false)
		throw FileException("File cannot be opened!");
	Event event;
	while (true) {
		try {
			is >> event;
			this->addEventToRepository(event);
		}
		catch (EventExceptions& e) {
			break;
		}
	}
	is.close();
}

void FileRepository::saveToFile() {
	std::filesystem::path path = std::filesystem::absolute(this->file_path);
	while (path.filename() != "Events-Manager") path = path.parent_path();
	path /= "data";
	path /= "Events.txt";
	std::ofstream os(path);
	if (os.is_open() == false)
		throw FileException("File cannot be opened!");
	for (auto& event : this->events) {
		os << event;
		os << std::endl;
	}
	os.close();
}
