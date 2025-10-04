#include "eventlist/CsvEventList.h"
#include <fstream>
#include <filesystem>
#include "exceptions/Exceptions.h"

void CsvEventList::saveToFile() const {
	std::filesystem::path path = std::filesystem::absolute(this->file_path);
	while (path.filename() != "Events-Manager") path = path.parent_path();
	path /= "data";
	path /= "EventList.csv";
	std::ofstream os(path);
	if (os.is_open() == false)
		throw FileException("File cannot be opened!");
	os << "Index, Title, Description, Date, Time, Number of People, Link" << std::endl;
	int idx = 1;
	for (auto& event : this->events) {
		os << idx++ << "," << event.getTitle() << "," << event.getDescription() << "," << event.getDate() << "," << event.getTime() << "," << event.getNumberOfPeople() << "," << event.getOnlineLink();
		os << std::endl;
	}
	os.close();
}