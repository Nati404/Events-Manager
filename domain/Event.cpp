#include "Event.h"
#include "utils/Utils.h"
#include "exceptions/Exceptions.h"
#include "validator/EventValidator.h"
#include <string>
#include <iostream>
#include <vector>
#include <format>

/// <summary>
/// Constructs the Event object with the given parameters.
/// </summary>
/// <param name="title">The title</param>
/// <param name="description">The description</param>
/// <param name="date_and_time">The date and time</param>
/// <param name="number_of_people">The numebr of people</param>
/// <param name="online_link">The online link</param>
Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& time, int number_of_people, const std::string& online_link) {
	this->title = title;
	this->description = description;
	this->date = date;
	this->time = time;
	this->number_of_people = number_of_people;
	this->online_link = online_link;
}

/// <summary>
/// Destructor. Dont need to do anything, C++ handles it by itself if we respect the rule of 3.
/// </summary>
Event::~Event() {}

// Getters
std::string Event::getTitle() const {
	return this->title;
}

std::string Event::getDescription() const {
	return this->description;
}

std::string Event::getDate() const {
	return this->date;
}

std::string Event::getTime() const {
	return this->time;
}

std::string Event::getDateAndTime() const {
	return this->date + " ; " + this->time;
}

int Event::getNumberOfPeople() const {
	return this->number_of_people;
}

std::string Event::getOnlineLink() const {
	return this->online_link;
}

//Setters


void Event::setTitle(const std::string& title) {
	this->title = title;
}

void Event::setDescription(const std::string& description) {
	this->description = description;
}

void Event::setNumberOfPeople(int number_of_people) {
	this->number_of_people = number_of_people;
}

void Event::setOnlineLink(const std::string& online_link) {
	this->online_link = online_link;
}

void Event::setDate(const std::string& date) {
	this->date = date;
}

void Event::setTime(const std::string& time) {
	this->time = time;
}

// Defines equality between two events to be the online_link (This is what makes an event unique).
bool Event::operator==(const Event& event) const {
	return this->online_link == event.online_link;
}

// Same as overloading for dynamic vector. Crucial for destruction. (Rule of 3).
Event& Event::operator=(const Event& event) {
	if (this == &event) return *this;
	this->title = event.title;
	this->description = event.description;
	this->date = event.date;
	this->time = event.time;
	this->number_of_people = event.number_of_people;
	this->online_link = event.online_link;
	return *this;
}

int Event::getMonth() const {
	Utils util;
	std::vector<std::string> data = util.tokenize(this->date, '-');
	return std::stoi(data[1]);
}

int Event::getYear() const {
	Utils util;
	std::vector<std::string> data = util.tokenize(this->date, '-');
	return std::stoi(data[0]);
}

int Event::getDay() const {
	Utils util;
	std::vector<std::string> data = util.tokenize(this->date, '-');
	return std::stoi(data[2]);
}

int Event::getHour() const {
	Utils util;
	std::vector<std::string> data = util.tokenize(this->time, ':');
	return std::stoi(data[0]);
}

int Event::getMinute() const {
	Utils util;
	std::vector<std::string> data = util.tokenize(this->time, ':');
	return std::stoi(data[1]);
}

// Overwrite the < operator for two events, returns true if the first event is
// earlier by date and time than the second one.
bool Event::operator < (const Event& event) const {
	int now = this->getYear() - event.getYear();
	if(now < 0) return true;
	else if (now > 0) return false;
	now = this->getMonth() - event.getMonth();
	if(now < 0) return true;
	else if (now > 0) return false;
	now = this->getDay() - event.getDay();
	if(now < 0) return true;
	else if (now > 0) return false;
	now = this->getHour() - event.getHour();
	if(now < 0) return true;
	else if (now > 0) return false;
	now = this->getMinute() - event.getMinute();
	if(now < 0) return true;
	else return false;
}

std::istream& operator >> (std::istream& is, Event& e) {
	Utils util;
	std::string input;
	std::getline(is, input);
	std::vector<std::string> elements = util.tokenize(input, ',');
	if (elements.size() != 6)
		throw EventExceptions("Invalid input format!");

	const std::string& title = elements[0];
	const std::string& description = elements[1];
	const std::string& date = elements[2];
	const std::string& time = elements[3];
	const std::string& number_of_people = elements[4];
	const std::string& online_link = elements[5];
	EventValidator::validateEventIdentifiers(title, description, date, time, number_of_people, online_link);
	e.setTitle(title);
	e.setDescription(description);
	e.setDate(date);
	e.setTime(time);
	e.setNumberOfPeople(std::stoi(number_of_people));
	e.setOnlineLink(online_link);
	return is;
}

std::ostream& operator << (std::ostream& os, const Event& e) {
	os << e.getTitle() << "," << e.getDescription() << "," << e.getDate() << "," << e.getTime() << "," << e.getNumberOfPeople() << "," << e.getOnlineLink();
	return os;
}

std::string Event::toString() const{
	return std::format("{} : {} : {} : {} : {}", this->title, this->description, this->getDateAndTime(), this->number_of_people, this->online_link);
}