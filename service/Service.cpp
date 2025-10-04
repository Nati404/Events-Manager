#include "domain/Event.h"
#include "exceptions/Exceptions.h"
#include "validator/EventValidator.h"
#include "eventlist/FileEventList.h"
#include "eventlist/HtmlEventList.h"
#include "eventlist/CsvEventList.h"
#include <time.h>
#include <algorithm>
#include "repository/UserRepository.h"
#include "Service.h"
// Constructor
Service::Service() {
	this->repository = nullptr;
	this->eventlist = nullptr;
}

// Destructor
Service::~Service() {
	//delete this->repository;
	//delete this->eventlist;
	for (Action* action : undoStack)
		delete action;
	undoStack.clear();
	for (Action* action : redoStack)
		delete action;
	redoStack.clear();
}

// Adds an element or throws exception if the element already exists in the repository.
void Service::addEventService(Event e) {
	if (this->repository->getPositionOfEvent(e) != -1) {
		throw DuplicateEventException();
	}
	this->repository->addEventToRepository(e);
	this->undoStack.push_back(new ActionAdd(e, this->repository));
	this->redoStack.clear();
}

// Removes an element from the repository or throws exception if no such element in the repo.
void Service::removeEventService(const Event& event) {
	int position = this->repository->getPositionOfEvent(event);
	if (position == -1) {
		throw EventNonExistentException();
	}
	Event nowevent = this->repository->getEventOnPosition(position);
	this->repository->removeEventFromRepository(position);
	this->undoStack.push_back(new ActionRemove(nowevent, this->repository));
	this->redoStack.clear();
}

// Updates an element from the repository or throws exception if:
// - No such element in the repo
// - The new online_link is already used by a different event (If the online_link doesnt change, it works - edge case).
void Service::updateEventService(const Event& event, const std::string& new_title, const std::string& new_description, const std::string& new_date, const std::string& new_time, int new_number_of_people, const std::string& new_link) {
	int position = this->repository->getPositionOfEvent(event);
	if (position == -1) {
		throw EventNonExistentException();
	}
	Event new_event = Event(new_title, new_description, new_date, new_time, new_number_of_people, new_link);
	EventValidator::validateEventIdentifiers(new_title, new_description, new_date, new_time, std::to_string(new_number_of_people), new_link);
	int position_of_new_event = this->repository->getPositionOfEvent(new_event);
	if (position_of_new_event != -1 && position_of_new_event != position) {
		throw DuplicateEventException();
	}
	Event old_event = this->repository->getEventOnPosition(position);
	this->repository->updateEventInRepository(position, new_event);
	this->undoStack.push_back(new ActionUpdate(old_event, new_event, this->repository));
	this->redoStack.clear();
}

// Returns a dynamic vector of all the events in the repo.
std::vector<Event> Service::displayEventsService() const {
	return this->repository->getEvents();
}

// Returns a dynamic vector of all the events in a given month.
std::vector<Event> Service::getEventsOnGivenMonth(int given_month) const {
	std::vector<Event> ans;
	std::vector<Event> events = this->repository->getEvents();
	if(given_month!=-1)
	std::copy_if(events.begin(), events.end(), std::back_inserter(ans), [&given_month](const Event& e) {return e.getMonth() == given_month; });
	else {
		std::sort(events.begin(), events.end());
		return events;
	}
	return ans;
}

// Generates a custom number of random events and adds them to the repo.
void Service::generateRandomEvents(int number) {
	std::string titles[] = {
	"Science Fair 2023",
	"Math Olympiad Competition",
	"Robotics Workshop",
	"Debate Club Championship",
	"Art and Craft Exhibition",
	"Music Band Performance Night",
	"Coding Hackathon",
	"Environmental Awareness Campaign",
	"Drama Club Play: Romeo and Juliet",
	"Chess Tournament",
	"Book Reading Club Meeting",
	"Sports Day: Annual Athletics Meet",
	"Photography Contest",
	"Cooking Masterclass",
	"Public Speaking Workshop",
	"Yoga and Meditation Session",
	"Community Service Day",
	"Film Screening: Classic Cinema",
	"Creative Writing Contest",
	"Cultural Fest: Global Traditions"
	};

	std::string descriptions[] = {
	"Showcase your innovative science projects and compete for prizes.",
	"Test your problem-solving skills in this challenging math contest.",
	"Learn to build and program robots in this hands-on workshop.",
	"Engage in lively debates on current topics and improve your public speaking skills.",
	"Display your creative artwork and crafts for the school community to admire.",
	"Enjoy live performances by the school's talented music bands.",
	"Collaborate with peers to create innovative software solutions in a 24-hour coding marathon.",
	"Participate in activities to promote sustainability and environmental conservation.",
	"Watch the Drama Club's performance of Shakespeare's classic tragedy.",
	"Compete in a strategic battle of wits in this annual chess competition.",
	"Discuss your favorite books and share insights with fellow book lovers.",
	"Cheer on your classmates in track and field events during this exciting day.",
	"Submit your best photos and compete for recognition in various categories.",
	"Learn to prepare delicious dishes from professional chefs in this interactive class.",
	"Develop confidence and skills to speak effectively in front of an audience.",
	"Relax and rejuvenate with guided yoga and meditation practices.",
	"Give back to the community through volunteering and service projects.",
	"Watch and discuss timeless films from the golden age of cinema.",
	"Submit your original stories, poems, or essays for a chance to win prizes.",
	"Celebrate diversity with performances, food, and traditions from around the world."
	};

	std::string eventDate[] = {
	"2023-11-15",
	"2023-11-17",
	"2023-11-20",
	"2023-11-22",
	"2023-11-25",
	"2023-11-28",
	"2023-12-01",
	"2023-12-03",
	"2023-12-05",
	"2023-12-08",
	"2023-12-10",
	"2023-12-12",
	"2023-12-15",
	"2023-12-18",
	"2023-12-20",
	"2023-12-22",
	"2023-12-25",
	"2023-12-28",
	"2023-12-30",
	"2024-01-05"
	};

	std::string eventTime[] = {
	"10:00",
	"14:00",
	"09:30",
	"16:00",
	"11:00",
	"18:00",
	"12:00",
	"13:00",
	"19:00",
	"15:00",
	"17:00",
	"08:00",
	"10:00",
	"14:00",
	"16:00",
	"09:00",
	"12:00",
	"18:00",
	"10:00",
	"14:00"
	};

	int randomNumbers[20] = {
	12, 25, 7, 18, 30,
	9, 22, 15, 6, 28,
	14, 20, 5, 27, 19,
	10, 23, 16, 8, 29
	};

	std::string eventLinks[20] = {
	"https://sciencefair2023.com",
	"https://matholympiad2023.com",
	"https://roboticsworkshop2023.com",
	"https://debatechampionship2023.com",
	"https://artexhibition2023.com",
	"https://musicbandnight2023.com",
	"https://codinghackathon2023.com",
	"https://environmentcampaign2023.com",
	"https://dramaclubplay2023.com",
	"https://chesstournament2023.com",
	"https://bookclubmeeting2023.com",
	"https://sportsday2023.com",
	"https://photographycontest2023.com",
	"https://cookingmasterclass2023.com",
	"https://publicspeaking2023.com",
	"https://yogameditation2023.com",
	"https://communityservice2023.com",
	"https://classiccinema2023.com",
	"https://writingcontest2023.com",
	"https://culturalfest2023.com"
	};

	srand(time(NULL));
	int cnt = number;
	while (cnt) {
		int nr = rand() % 20;
		Event event = Event(titles[nr], descriptions[nr], eventDate[nr], eventTime[nr], randomNumbers[nr], eventLinks[nr]);
		try {
			this->addEventService(event);
			cnt--;
		}
		catch (DuplicateEventException& err) {
			continue;
		}
	}
}

// Opens the link of the given event in the browser if it is valid
// Otherwise throw an exception.
void Service::openEventInBrowser(Event event) const {
	std::string link = event.getOnlineLink();
	std::string command = "start " + link;
	int result = system(command.c_str());
	if (result != 0) throw BrowserError();
}

// Adds the given event to the user's list of events and increases said event's
// number of people in attendance. If the event is already in the user's list
// throws an exception.
void Service::addEventToUserList(Event e) {
	if (this->eventlist->getPositionOfEvent(e) != -1) {
		throw DuplicateEventException();
	}
	e.setNumberOfPeople(e.getNumberOfPeople() + 1);
	this->eventlist->addEvent(e);
	this->repository->updateEventInRepository(this->repository->getPositionOfEvent(e), e);
}

// Deletes an event from the user's list if it exists. Else throws an exception.
// If the event is successfully deleted, decreases the number of people attending the event.
void Service::deleteEventFromUserList(Event e) {
	if (this->eventlist->getPositionOfEvent(e) == -1) {
		throw EventNonExistentException();
	}
	this->eventlist->removeEvent(e);
	Event actual_event = this->repository->getEventOnPosition(this->repository->getPositionOfEvent(e));
	Event new_event = Event(actual_event.getTitle(), actual_event.getDescription(), actual_event.getDate(), actual_event.getTime(), actual_event.getNumberOfPeople() - 1, e.getOnlineLink());
	this->repository->updateEventInRepository(this->repository->getPositionOfEvent(e), new_event);
}

// Returns a dynamic vector of all the events in the user's list
std::vector<Event> Service::getEventInUserList() const {
	std::vector<Event> ans;
	for (auto& e : this->eventlist->getEventsInUserList()) {
		ans.push_back(e);
	}
	return ans;
}

void Service::setEventListType(int type) {
	if (type == 0) {
		this->eventlist = new UserRepository();
	}
	else if (type == 1) {
		this->eventlist = new CsvEventList("../data/EventList.csv");
	}
	else if (type == 2) {
		this->eventlist = new HtmlEventList("../data/EventList.html");
	}
	else
		throw RepositoryException("Invalid list type!");
}

void Service::setRepositoryType(int type) {
	if (type == 0) {
		this->repository = new Repository();
	}
	else if (type == 1) {
		this->repository = new FileRepository("data/Events.txt");
		this->repository->readFromFile();
	}
	else
		throw RepositoryException("Invalid list type!");
}

void Service::openInAppService() {
	this->eventlist->openInApp();
}

void Service::undoService() {
	if (this->undoStack.empty())
		throw std::exception("No operation to be undone.");
	this->undoStack.back()->executeUndo();
	this->redoStack.push_back(std::move(this->undoStack.back())); 
	this->undoStack.pop_back();
}


void Service::redoService() {
	if (this->redoStack.empty())
		throw std::exception("No operation to be redone.");
	this->redoStack.back()->executeRedo();
	this->undoStack.push_back(std::move(this->redoStack.back())); 
	this->redoStack.pop_back();
}
