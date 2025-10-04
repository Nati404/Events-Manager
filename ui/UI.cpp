#include "UI.h"
#include "exceptions/Exceptions.h"
#include "validator/EventValidator.h"
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
UI::UI() {
	this->service = Service();
}

UI::~UI() {}

void UI::admin_menu() {
	std::cout << "Menu:\n";
	std::cout << "1. Add Event\n";
	std::cout << "2. Remove Event\n";
	std::cout << "3. Update Event\n";
	std::cout << "4. Display all events\n";
	std::cout << "5. Exit\n";
}

void UI::admin_operations_ui() {
	while (true) {
		this->admin_menu();
		int option = 0;
		while (option <= 0 || option > 5) {
			std::cout << "Input what you would like to do: ";
			std::cin >> option;
			if (option <= 0 || option > 5) {
				std::cout << "Please input a valid command!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		switch (option) {
		case 5:
			return;
			break;
		case 1:
			this->addEventUI();
			break;
		case 2:
			this->removeEventUI();
			break;
		case 3:
			this->updateEventUI();
			break;
		case 4:
			this->displayEventsUI();
			break;
		}
	}
}

void UI::user_operations_ui() {
	while (true) {
		this->user_menu();
		int option = 0;
		while (option <= 0 || option > 5) {
			std::cout << "Input what you would like to do: ";
			std::cin >> option;
			if (option <= 0 || option > 5) {
				std::cout << "Please input a valid command!" << std::endl;
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		}
		switch (option) {
		case 5:
			return;
			break;
		case 1:
			this->seeEventsUserUI();
			break;
		case 2:
			this->deleteEventFromListUserUI();
			break;
		case 3:
			// VERY IMPORTANT! Ask if the information should be updated in the user list
			// if it's updated by the administrator ( if the event information is modified
			// after it is added into the user list.
			this->seeEventsAttendedUserUI();
			break;
		case 4:
			this->service.openInAppService();
			break;
		}
	}
}

void UI::start() {
	//this->service.generateRandomEvents(10);
	this->setRepositoryTypeUI();
	this->setEventListTypeUI();
	int mode = 0;
	while (true) {
		while (mode < 1 || mode > 3) {
			std::cout << "Choose what you are: " << std::endl;
			std::cout << "1. Admin" << std::endl;
			std::cout << "2. User" << std::endl;
			std::cout << "3. Exit" << std::endl;
			std::cin >> mode;
		}
		if (mode == 1) {
			this->admin_operations_ui();
			mode = -1;
		}
		else if (mode == 2) {
			this->user_operations_ui();
			mode = -1;
		}
		else return;
	}
}

void UI::addEventUI() {
	std::string aux;
	std::getline(std::cin, aux);
	Event event;
	try {
		std::cin >> event;
	}
	catch (EventExceptions& errors) {
		std::cout << "Errors in reading the event: " << std::endl;
		for (const auto& error : errors.returnErrors()) {
			std::cout << error.what() << std::endl;
		}
		return;
	}
	try {
		this->service.addEventService(event);
	}
	catch (DuplicateEventException& err) {
		std::cerr << "Error: " << err.what() << std::endl;
	}
}

void UI::removeEventUI() {
	std::string online_link, aux;
	std::getline(std::cin, aux);
	std::cout << "Input the link of the even you wish to delete: ";
	std::getline(std::cin, online_link);
	Event event = Event("", "", "", "", 0, online_link);
	try {
		this->service.removeEventService(event);
		std::cout << "Event removed successfully!" << std::endl;
	}
	catch (EventNonExistentException& err) {
		std::cerr << "Error: " << err.what() << std::endl;
	}

}

void UI::updateEventUI() {
	std::string initial_link, aux, new_title, new_description, new_date, new_time, new_online_link;
	int new_number_of_people = 0;
	std::getline(std::cin, aux);
	std::cout << "Input the link of the event you wish to update: " << std::endl;
	std::getline(std::cin, initial_link);
	Event event = Event("", "", "", "", 0, initial_link);
	std::cout << "Input the new title of the event: ";
	std::getline(std::cin, new_title);
	std::cout << "Input the new description of the event: ";
	std::getline(std::cin, new_description);
	std::cout << "Input the new date of the event: ";
	std::getline(std::cin, new_date);
	std::cout << "Input the new time of the event: ";
	std::getline(std::cin, new_time);
	while (new_number_of_people <= 0) {
		std::cout << "Input event number of people: ";
		std::cin >> new_number_of_people;
		if (new_number_of_people <= 0) {
			std::cout << "Please input a positive integer!" << std::endl;
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}
	std::getline(std::cin, aux);
	std::cout << "Input the new online link of the event: ";
	std::getline(std::cin, new_online_link);
	try {
		this->service.updateEventService(event, new_title, new_description, new_date, new_time, new_number_of_people, new_online_link);
	}
	catch (EventExceptions& errors) {
		std::cout << "Errors in new event: \n";
		for (auto& err : errors.returnErrors())
			std::cout << err.what() << std::endl;
		return;
	}
	catch (EventNonExistentException& err) {
		std::cout << "Error: " << err.what() << std::endl;
	}
	catch (DuplicateEventException& err) {
		std::cout << "Error: " << err.what() << std::endl;
	}
}

void UI::displayEventsUI() {
	std::vector<Event> events = this->service.displayEventsService();
	int cnt = 1;
	for (const Event& e : events) {
		std::cout << cnt << " - " << e << '\n';
		cnt++;
	}
}

void UI::user_menu() {
	std::cout << "Menu:" << std::endl;
	std::cout << "1. See events" << std::endl;
	std::cout << "2. Delete event from list" << std::endl;
	std::cout << "3. See events you attend" << std::endl;
	std::cout << "4. Open attended events list in external app" << std::endl;
	std::cout << "5. Exit" << std::endl;
}

void UI::seeEventsUserUI() {
	std::string given_month = "", aux;
	std::cout << "Enter the given month: ";
	std::getline(std::cin, aux);
	std::getline(std::cin, given_month);
	std::vector<Event> events;
	int given_month_int = 0;
	// User input a specific month
	if (given_month.empty()) given_month_int = -1;
	else given_month_int = std::stoi(given_month);
	events = this->service.getEventsOnGivenMonth(given_month_int);
	if (events.size() == 0) {
		std::cout << "There is no event to display." << std::endl;
		return;
	}
	int idx = 0;
	while (true) {
		//std::cout<<idx<<" "<<events.getSize()<<std::endl;
		if (idx >= events.size()) idx = 0;
		Event e = events[idx];
		std::cout << "Event " << idx + 1 << ":" << std::endl;
		std::cout << e << std::endl;
		try {
			this->service.openEventInBrowser(e);
		}
		catch (BrowserError& err) {
			std::cout << err.what() << std::endl;
		}
		int option = 0;
		std::cout << "1. Go next" << std::endl;
		std::cout << "2. Add event to list" << std::endl;
		std::cout << "3. Exit slideshow" << std::endl;
		while (option < 1 || option > 3) {
			std::cin >> option;
			switch (option) {
			case 1:
				idx++;
				break;
			case 2:
				try {
					this->service.addEventToUserList(e);
					std::cout << "Event added successfully!" << std::endl;
				}
				catch (std::invalid_argument& err) {
					std::cout << err.what() << std::endl;
				}
				option = -1;
				break;
			case 3:
				return; // Exit slideshow completly
				break;
			}
		}
	}
}

void UI::deleteEventFromListUserUI() {
	std::string link, aux;
	std::cout << "Enter the link of the event you wish to remove: " << std::endl;
	std::getline(std::cin, aux);
	std::getline(std::cin, link);
	try {
		Event e = Event("", "", "", "", 0, link);
		this->service.deleteEventFromUserList(e);
	}
	catch (EventNonExistentException& err) {
		std::cout << err.what() << std::endl;
	}
}

void UI::seeEventsAttendedUserUI() {
	std::vector<Event> events = this->service.getEventInUserList();
	if (events.size() == 0) {
		std::cout << "There is no event to display." << std::endl;
	}
	else {
		int cnt = 1;
		for (const Event& e : events) {
			std::cout << cnt << ": " << e << std::endl;
			cnt++;
		}
	}
}

void UI::setRepositoryTypeUI() {
	int file_type = 0;
	while (file_type < 1 || file_type > 2) {
		std::cout << "Choose the repository you want: " << std::endl;
		std::cout << "1. File" << std::endl;
		std::cout << "2. DB" << std::endl;
		std::cin >> file_type;
	}
	try {
		this->service.setRepositoryType(file_type);
	}
	catch (RepositoryException& err) {
		std::cout << err.what() << std::endl;
	}
}

void UI::setEventListTypeUI() {
	int file_type = 0;
	while (file_type < 1 || file_type > 2) {
		std::cout << "Choose the save format you want: " << std::endl;
		std::cout << "1. CSV" << std::endl;
		std::cout << "2. HTML" << std::endl;
		std::cin >> file_type;
	}
	try {
		this->service.setEventListType(file_type);
	}
	catch (RepositoryException& err) {
		std::cout << err.what() << std::endl;
	}
}