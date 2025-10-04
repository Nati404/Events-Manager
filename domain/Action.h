#pragma once
#include "domain/Event.h"
#include "repository/Repository.h"

class Action {
public:
	Action() {}
	virtual void executeUndo() const = 0;
	virtual void executeRedo() const = 0;
	virtual ~Action() {}
};

class ActionAdd : public Action {
private:
	Event addedEvent;
	Repository* repo;
public:
	ActionAdd(Event event, Repository* repo) : addedEvent{ event }, repo{ repo } {};
	void executeUndo() const override;
	void executeRedo() const override;
};

class ActionRemove : public Action {
private:
	Event removedEvent;
	Repository* repo;
public:
	ActionRemove(Event event, Repository* repo) : removedEvent{ event }, repo{ repo } {};
	void executeUndo() const override;
	void executeRedo() const override;

};

class ActionUpdate : public Action {
private:
	Event first_event;
	Event second_event;
	Repository* repo;
public:
	ActionUpdate(Event first_event, Event second_event, Repository* repo)
		: first_event(std::move(first_event)), second_event(std::move(second_event)), repo(repo) {
	}
	void executeUndo() const override;
	void executeRedo() const override;
};
