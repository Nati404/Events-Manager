#include "Repository.h"
#include "domain/Event.h"

// Destructor
Repository::~Repository() {}

// Adds an event to the repository.
void Repository::addEventToRepository(const Event& e) {
	this->events.push_back(e);
}

// Removes the element from a given position.
void Repository::removeEventFromRepository(int position) {
	//this->events.removeElementOnPosition(position);
	this->events.erase(this->events.begin() + position);
}

// Updates the element from a given position to a new given event.
void Repository::updateEventInRepository(int position, const Event& new_event) {
	this->events[position] = new_event;
}

// Returns a DynamicVector containing all the events in the repository.
std::vector<Event> Repository::getEvents() const{
	return this->events;
}

// Returns the number of events in the repo.
int Repository::getNumberOfEvents() {
	return this->events.size();
}

// Returns the element from the repo from a given position.
Event Repository::getEventOnPosition(int position) {
	return this->events[position];
}

// Returns the position of a given element in the repository or -1 if no such element
// in repository. 
int Repository::getPositionOfEvent(const Event& event) const{
	/*int cnt = 0;
	if (this->events.empty()) return -1;
	for(const Event& e : this->events) {
		if (e==event) return cnt;
		cnt++;
	}
	return -1;
	*/
	auto it = find(this->events.begin(), this->events.end(), event);
	if (it == this->events.end()) return -1;
	return it - this->events.begin();
}