#pragma once
#include <QDialog>
#include <QTableView>
#include <QVBoxLayout>
#include "AttendedEventsTableModel.h"
#include "service/Service.h"

class AttendedTableDialog : public QDialog {
	Q_OBJECT

public:
	AttendedTableDialog(Service& service, QWidget* parent = nullptr);
};