#pragma once
#include "service/Service.h"

class UI {
	private:
		Service service;
		void admin_menu();
		void user_menu();
		void addEventUI();
		void removeEventUI();
		void updateEventUI();
		void displayEventsUI();
		void seeEventsUserUI();
		void deleteEventFromListUserUI();
		void seeEventsAttendedUserUI();
		void admin_operations_ui();
		void user_operations_ui();
		void setEventListTypeUI();
		void setRepositoryTypeUI();
	public:
		UI();
		~UI();
		void start();
};