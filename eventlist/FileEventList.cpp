#include "FileEventList.h"
#include <filesystem>
void FileEventList::openInApp() {
	this->saveToFile();
	std::filesystem::path path = std::filesystem::absolute(this->file_path);
	while (path.filename() != "Events-Manager") path = path.parent_path();
	path /= "data";
	path /= this->file_path;
	std::string pathString{ path.generic_string()};
	std::string command = "start " + pathString;
	system(command.c_str());
}

void FileEventList::addEvent(Event event) {
	UserRepository::addEvent(event);
	this->saveToFile();
}

void FileEventList::removeEvent(Event event) {
	UserRepository::removeEvent(event);
	this->saveToFile();
}