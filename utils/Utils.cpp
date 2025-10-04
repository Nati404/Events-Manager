	#include "Utils.h"
#include <string>
#include <vector>
#include <sstream>

void Utils::removeStringBorderWhiteSpaces(std::string& s) {
	while (!s.empty() && s[0] == ' ') {
		s.erase(0, 1);
	}
	while (!s.empty() && s[s.size() - 1] == ' ') {
		s.erase(s.size() - 1, 1);
	}
}

std::vector<std::string> Utils::tokenize(const std::string& s, char delimiter) {
	std::vector<std::string> ret;
	std::stringstream stream{s};
	std::string token;
	while (std::getline(stream, token, delimiter)) {
		removeStringBorderWhiteSpaces(token);
		ret.push_back(token);
	}
	return ret;
}