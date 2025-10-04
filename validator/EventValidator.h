#pragma once
#include <vector>
#include <exception>
#include <string>

class EventExceptions {
private:
	std::vector<std::exception> errors;
public:
	EventExceptions(std::vector<std::exception> errors) : errors(errors) {};
	EventExceptions(std::string error) : errors({ std::exception(error.c_str()) }) {};
	std::vector<std::exception> returnErrors();
};

class EventValidator {
public:
	static void validateEventTitle(const std::string& title);
	static void validateEventDescription(const std::string& description);
	static void validateEventDate(const std::string& date);
	static void validateEventTime(const std::string& time);
	static void validateEventNumberOfPeople(const std::string& number_of_people);
	static void validateEventOnlineLink(const std::string& online_link);
	static void validateEventIdentifiers(
		const std::string& title,
		const std::string& description,
		const std::string& date,
		const std::string& time,
		const std::string& number_of_people,
		const std::string& online_link
	);

};
