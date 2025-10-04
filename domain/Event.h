#pragma once
#include <string>
#include <iostream>
#include <vector>

	class Event {
		private:
			std::string title;
			std::string description;
			std::string date;
			std::string time;
			int number_of_people;
			std::string online_link;
		public:
			Event(const std::string &title = "", const std::string& description = "", const std::string &date = "", const std::string& time="", int number_of_people = 0, const std::string & online_link = "");
			Event(const Event& other) noexcept : title(other.title), description(other.description), date(other.date), time(other.time), number_of_people(other.number_of_people), online_link(other.online_link) {}
			~Event();
			std::string getTitle() const;
			std::string getDescription() const;
			std::string getDate() const;
			std::string getTime() const;
			std::string getDateAndTime() const;
			int getNumberOfPeople() const;
			int getMonth() const;
			int getYear() const;
			int getDay() const;
			int getHour() const;
			int getMinute() const;
			std::string getOnlineLink() const;
			void setTitle(const std::string& title);
			void setDescription(const std::string& description);
			void setNumberOfPeople(int number_of_people);
			void setOnlineLink(const std::string& online_link);
			void setDate(const std::string& date);
			void setTime(const std::string& time);
			bool operator==(const Event& event) const;
			bool operator < (const Event& event) const;
			std::string toString() const;
			Event& operator=(const Event& event);
			friend std::istream& operator >> (std::istream& is, Event& e);
			friend std::ostream& operator << (std::ostream& os, const Event& e);
			//Event(const Event&) noexcept = default;
			//Event& operator=(const Event&) noexcept = default;
			Event(Event&&) noexcept = default;
			Event& operator=(Event&&) noexcept = default;

	};
