#pragma once
#include "eventlist/FileEventList.h"

class HtmlEventList : public FileEventList {
public:
	HtmlEventList() {}
	HtmlEventList(const std::string& file_path) : FileEventList{ file_path } {}
	void saveToFile() const;
};