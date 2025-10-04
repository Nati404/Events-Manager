#include "AttendedEventsTableModel.h"

AttendedEventsTableModel::AttendedEventsTableModel(QObject* parent) : QAbstractTableModel(parent) {}

void AttendedEventsTableModel::loadEvents(const std::vector<Event>& events) {
	beginResetModel();
	this->attendedEvents = events;
	endResetModel();
}

int AttendedEventsTableModel::rowCount(const QModelIndex&) const {
	return (int)attendedEvents.size();
}

int AttendedEventsTableModel::columnCount(const QModelIndex&) const {
	return 6;
}

QVariant AttendedEventsTableModel::data(const QModelIndex& index, int role) const {
	if (!index.isValid() || role != Qt::DisplayRole)
		return {};

	const Event& e = attendedEvents[index.row()];
	switch (index.column()) {
	case 0: return QString::fromStdString(e.getTitle());
	case 1: return QString::fromStdString(e.getDescription());
	case 2: return QString::fromStdString(e.getDate());
	case 3: return QString::fromStdString(e.getTime());
	case 4: return QString::fromStdString(std::to_string(e.getNumberOfPeople()));
	case 5: return QString::fromStdString(e.getOnlineLink());
	default: return {};
	}
}

QVariant AttendedEventsTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
		return {};
	switch (section) {
	case 0: return "Title";
	case 1: return "Description";
	case 2: return "Date";
	case 3: return "Time";
	case 4: return "Number of People";
	case 5: return "Link";
	}
}

