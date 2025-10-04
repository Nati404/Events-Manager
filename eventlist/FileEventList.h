#pragma once
#include "repository/UserRepository.h"
#include <string>
class FileEventList : public UserRepository{
protected:
	std::string file_path;
public:
	FileEventList() {};
	FileEventList(const std::string& file_path) : file_path{ file_path } {}
	void addEvent(Event) override;
	void removeEvent(Event) override;
	virtual void saveToFile() const = 0;
	void openInApp();
	virtual ~FileEventList() {};
};