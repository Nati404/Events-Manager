#include "AttendedTableDialog.h"

AttendedTableDialog::AttendedTableDialog(Service& service, QWidget* parent)
    : QDialog(parent) {
    setWindowTitle("Attended Events");
    resize(800, 600);

    auto* model = new AttendedEventsTableModel(this);
    model->loadEvents(service.getEventInUserList());

    auto* tableView = new QTableView(this);
    tableView->setModel(model); 
    tableView->resizeColumnsToContents();

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);
    setLayout(layout);
}