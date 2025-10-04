#pragma once
#include "domain/Event.h"
#include <vector>

class Repository {
protected:
	std::vector<Event> events;
public:
	Repository() : events(std::vector<Event>(0)) {}
	virtual ~Repository();
	virtual void readFromFile() {};
	virtual void addEventToRepository(const Event& e);
	virtual void removeEventFromRepository(int position);
	virtual void updateEventInRepository(int position, const Event& new_event);
	std::vector<Event> getEvents() const;
	int getNumberOfEvents();
	Event getEventOnPosition(int position);
	int getPositionOfEvent(const Event& e) const;
};