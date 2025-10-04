#include "Action.h"

void ActionAdd::executeUndo() const {
	this->repo->removeEventFromRepository(this->repo->getPositionOfEvent(this->addedEvent));
}

void ActionAdd::executeRedo() const {
	this->repo->addEventToRepository(this->addedEvent);
}

void ActionRemove::executeUndo() const {
	this->repo->addEventToRepository(this->removedEvent);
}

void ActionRemove::executeRedo() const {
	this->repo->removeEventFromRepository(this->repo->getPositionOfEvent(this->removedEvent));
}

void ActionUpdate::executeUndo() const {
	this->repo->updateEventInRepository(this->repo->getPositionOfEvent(this->second_event), this->first_event);
}

void ActionUpdate::executeRedo() const {
	this->repo->updateEventInRepository(this->repo->getPositionOfEvent(this->first_event), this->second_event);
}