    #include "UserRepository.h"
    // Adds the given event to the user repository.
    void UserRepository::addEvent(Event event) {
        this->events.push_back(event);
    }

    // Removes the given event from the user repository, assumes the event is in the repository.
    void UserRepository::removeEvent(Event event) {
        this->events.erase(this->events.begin() + this->getPositionOfEvent(event));
    }

    // Returns the event on the given position from the user repository.
    // Assumes the given position is valid.
    Event UserRepository::getEventOnPosition(int pos) const {
        return this->events[pos];
    }

    // Returns the position of a given event in the user repository if it exists.
    // Otherwise returns -1.
    int UserRepository::getPositionOfEvent(Event event) const {
        int cnt = 0;
        for(auto& e : this->events) {
            if(e == event) {
                return cnt;
            }
            cnt++;
        }
        return -1;
    }

    // Returns the size of the user repository.
    int UserRepository::getSize() const {
        return this->events.size();
    }

    std::vector<Event> UserRepository::getEventsInUserList() const{
        return this->events;
    }