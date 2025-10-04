#include "eventlist/HtmlEventList.h"
#include "exceptions/Exceptions.h"
#include <fstream>
#include <filesystem>
void HtmlEventList::saveToFile() const{
	std::filesystem::path path = std::filesystem::absolute(this->file_path);
	while (path.filename() != "Events-Manager") path = path.parent_path();
	path /= "data";
	path /= "EventList.html";
	std::ofstream os(path);
	if (os.is_open() == false)
		throw FileException("File cannot be opened!");
	os << "<!DOCTYPE html> <html> <head> <title> Event WatchList</title> </head > <body> <table border=\"1\">";
	os << "<tr> <td> Index </td> <td> Title </td> <td> Description </td> <td> Date </td> <td> Time </td> <td> Number of people </td> <td> Link </td>";
	int idx = 1;
	for (auto& event : this->events) {
		os << "<tr> <td>" << idx++ << "</td> <td>" << event.getTitle() << "</td> <td> " << event.getDescription() << "</td> <td> " << event.getDate() << "</td> <td>" << event.getTime() << "</td> <td>"
			<< event.getNumberOfPeople() << "</td> <td> <a href=\"" << event.getOnlineLink() << "\">" << event.getOnlineLink() << "</a> </td> </tr>";
	}
	os << "</table> </body> </html>";
	os.close();
}