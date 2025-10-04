#pragma once
#include "domain/Event.h"
#include <vector>

class UserRepository {
protected:
    std::vector<Event> events;
public:
    UserRepository() {}
    virtual ~UserRepository() {};
    virtual void addEvent(Event);
    virtual void removeEvent(Event);
    virtual void openInApp() {};
    std::vector<Event> getEventsInUserList() const;
    Event getEventOnPosition(int) const;
    int getPositionOfEvent(Event) const;
    int getSize() const;
};
