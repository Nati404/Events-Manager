#pragma once
#include "Repository.h"
#include <filesystem>
class FileRepository : public Repository {
private:
	std::string file_path;
public:
	FileRepository() {};
	FileRepository(const std::string& file_path) : file_path{file_path} {};
	virtual ~FileRepository();
	void addEventToRepository(const Event& e) override;
	void removeEventFromRepository(int position) override;
	void updateEventInRepository(int position, const Event& new_event) override;
	void readFromFile();
	void saveToFile();
};	