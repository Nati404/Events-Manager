#include "FileEventList.h"
void FileEventList::openInApp() {
	this->saveToFile();
	std::string command = "start " + this->file_path;
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