#pragma once
#include <string>
#include <vector>

class Utils {
public:
	void removeStringBorderWhiteSpaces(std::string& s);
	std::vector<std::string> tokenize(const std::string& s, char delimiter);
};
