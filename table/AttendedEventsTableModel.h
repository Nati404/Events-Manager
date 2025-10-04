#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "domain/Event.h"

class AttendedEventsTableModel : public	QAbstractTableModel {
	Q_OBJECT;

private:
	std::vector<Event> attendedEvents;
public:
	explicit AttendedEventsTableModel(QObject* parent = nullptr);

	void loadEvents(const std::vector<Event>& events);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};