#include "EventValidator.h"
#include "utils/Utils.h"
#include "exceptions/Exceptions.h"
#include <vector>
void EventValidator::validateEventTitle(const std::string& title) {
	if (title.empty()) 
		throw std::exception("Event title cannot be empty!");
}

void EventValidator::validateEventDescription(const std::string& description) {
	if (description.empty())
		throw std::exception("Event description cannot be empty");

}

void EventValidator::validateEventDate(const std::string& date) {
	Utils util;
	if (date.empty())
		throw std::exception("Event date and time cannot be empty!");
	std::vector<std::string> elements = util.tokenize(date, '-');
	if (elements.size() != 3)
		throw std::exception("Event date format is incorect! The valid format is YYYY-MM-DD");
	int year;
	try {
		year = std::stoi(elements[0]);
	}
	catch (std::exception& e) {
		throw std::exception("Event year must be an integer!");
	}
	if (year < 0)
		throw std::exception("Event year must be a positive integer!");
	int month;
	try {
		month = std::stoi(elements[1]);
	}
	catch (std::exception& e) {
		throw std::exception("Event month must be an integer!");
	}
	if (month < 1 || month > 12)
		throw std::exception("Event month must be an integer between 1 and 12!");
	int day;
	try {
		day = std::stoi(elements[2]);
	}
	catch (std::exception& e) {
		throw std::exception("Event day must be an integer!");
	}

	int maxDays=31;
	switch (month) {
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		maxDays = 31;
		break;
	case 4: case 6: case 9: case 11:
		maxDays = 30;
		break;
	case 2:
		if ((year % 400 == 0) || (year % 100 != 0 && year % 4 == 0))
			maxDays = 29;
		else
			maxDays = 28;
		break;
	}

	if (day > maxDays)
		throw std::exception("Day cannot be greater than the number of days in the event month!");
}

void EventValidator::validateEventTime(const std::string& time) {
	Utils util;
	std::vector<std::string> elements = util.tokenize(time, ':');
	if (elements.size() != 2)
		throw std::exception("Event time format is incorect! The valid format is HH:MM");
	int hour, minutes;
	try {
		hour = std::stoi(elements[0]);
	}
	catch (std::exception& e) {
		throw std::exception("Event hour must be an integer!");
	}
	try {
		minutes = std::stoi(elements[1]);
	}
	catch (std::exception& e) {
		throw std::exception("Event minutes must be an integer!");
	}
	if (hour < 0 || hour > 23)
		throw std::exception("Event hour must be an integer between 0 and 23!");
	if (minutes < 0 || minutes > 59)
		throw std::exception("Event minutes must be between 0 and 59!");
}

void EventValidator::validateEventNumberOfPeople(const std::string& number_of_people) {
	int number_of_people_int = 0;
	try {
		number_of_people_int = std::stoi(number_of_people);
	}
	catch (std::exception& e) {
		throw std::exception("Event number of people must be an integer!");
	}
	if (number_of_people_int <= 0)
		throw std::exception("Event must have a strictly positive number of people attending!");
}

void EventValidator::validateEventOnlineLink(const std::string& online_link) {
	if (online_link.empty())
		throw std::exception("Event online link cannot be empty!");
}

void EventValidator::validateEventIdentifiers(
	const std::string& title,
	const std::string& description,
	const std::string& date,
	const std::string& time,
	const std::string& number_of_people,
	const std::string& online_link
) {
	std::vector<std::exception> errors;
	try {
		validateEventTitle(title);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}
	try {
		validateEventDescription(description);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}
	try {
		validateEventDate(date);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}
	try {
		validateEventTime(time);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}
	try {
		validateEventNumberOfPeople(number_of_people);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}
	try {
		validateEventOnlineLink(online_link);
	}
	catch (const std::exception& e) {
		errors.push_back(e);
	}

	if (errors.size() > 0)
		throw EventExceptions(errors);
}

std::vector<std::exception> EventExceptions::returnErrors() {
	return this->errors;
}
