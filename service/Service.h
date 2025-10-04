#pragma once
#include "repository/FileRepository.h" 
#include "eventlist/FileEventList.h"
#include "domain/Action.h"
class Service {
	private:
		Repository* repository;
		UserRepository* eventlist;
		std::vector<Action*> undoStack;
		std::vector<Action*> redoStack;
	public:
		Service();
		~Service();
		Service(const std::string& file_path);
		void addEventService(Event e);
		void removeEventService(const Event& e);
		void updateEventService(const Event& e, const std::string& new_title, const std::string& new_description, const std::string& new_date, const std::string& new_time, int new_number_of_people, const std::string& new_link);
		std::vector<Event> displayEventsService() const;
		std::vector<Event> getEventsOnGivenMonth(int)const;
		void generateRandomEvents(int number);
		void openEventInBrowser(Event) const;
		void addEventToUserList(Event e);
		void deleteEventFromUserList(Event);
		std::vector<Event> getEventInUserList() const;
		void setEventListType(int type);
		void setRepositoryType(int type);
		void openInAppService();
		void undoService();
		void redoService();
};