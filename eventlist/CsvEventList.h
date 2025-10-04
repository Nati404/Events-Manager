#pragma once
#include "FileEventList.h"
class CsvEventList : public FileEventList {
public:
	CsvEventList() {}
	CsvEventList(const std::string& file_path) : FileEventList{file_path} {}
	void saveToFile() const override;
};