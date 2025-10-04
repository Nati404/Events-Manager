#include "mainwindow.h"
#include <qboxlayout.h>
#include <QtWidgets/QLabel>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QMessageBox>
#include <QTimer>
#include <QShortcut>
#include <map>
#include <string>
#include <exception>
#include <sstream>
#include "utils/Utils.h"
#include "validator/EventValidator.h"
#include "exceptions/Exceptions.h"
#include "widgets/BarChartWidget.h"
#include "table/AttendedTableDialog.h"

mainwindow::mainwindow()
{
    Service service;
    service.setRepositoryType(1);
    service.setEventListType(0);
    this->service = service;
    this->stackedLayout = new QStackedLayout;
    this->setLayout(stackedLayout);
    setupStartingUI();
    setupAdminUI();
    setupUserUI();
    setupEventListTypeUI();
    setupChooseMonthUI();
    setupEventSlideshowUI();
    setupChartUI();
    this->populateList();
    stackedLayout->setCurrentWidget(chooseEventListTypeScreen);
    this->resize(1366, 768);
}

void mainwindow::setupStartingUI() {
    this->startScreen = new QWidget{};
    QVBoxLayout* layout = createChooseUserOrAdminMenuLayout();
    startScreen->setLayout(layout);
    stackedLayout->addWidget(startScreen);
}

void mainwindow::setupEventListTypeUI() {
    this->chooseEventListTypeScreen = new QWidget{};
    QVBoxLayout* layout = createChooseEventListTypeLayout();
    chooseEventListTypeScreen->setLayout(layout);
    stackedLayout->addWidget(chooseEventListTypeScreen);
}

void mainwindow::setupChooseMonthUI() {
    this->chooseMonthScreen = new QWidget{};
    QVBoxLayout* layout = createChooseMonthLayout();
    chooseMonthScreen->setLayout(layout);
    stackedLayout->addWidget(chooseMonthScreen);
}

void mainwindow::setupEventSlideshowUI() {
    this->userSlideShowScreen = new QWidget{};
    QVBoxLayout* layout = createUserSlideshowLayout();
    userSlideShowScreen->setLayout(layout);
    stackedLayout->addWidget(userSlideShowScreen);
}

void mainwindow::setupAdminUI() {
    this->adminScreen = new QWidget{};
    QHBoxLayout* layout = new QHBoxLayout{};
    QVBoxLayout* listLayout = new QVBoxLayout{};
    QLabel* title = new QLabel{ "Event list" };
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    title->setFont(titleFont);

    this->eventsListW = new QListWidget{};
    eventsListW->setStyleSheet("QListWidget::item:selected { background-color: #87CEFA; }");
    //this->eventsListW->setSelectionMode(QAbstractItemView::SingleSelection);
    //this->eventsListW->setSelectionBehavior(QAbstractItemView::SelectRows);    

    this->populateList();

    listLayout->addWidget(title);
    listLayout->addWidget(eventsListW);

    layout->addLayout(listLayout);
    layout->addLayout(createAdminOperationsLayout());

    adminScreen->setLayout(layout);
    stackedLayout->addWidget(adminScreen);
}

void mainwindow::setupUserUI() {
    this->userScreen = new QWidget{};
    QHBoxLayout* layout = new QHBoxLayout{};
    QVBoxLayout* listLayout = new QVBoxLayout{};

    QLabel* title = new QLabel{ "Attended Events:" };
    title->setAlignment(Qt::AlignCenter);
    QFont titleFont;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    title->setFont(titleFont);

    this->attendedEventsListW = new QListWidget{};
    this->attendedEventsListW->setSelectionMode(QAbstractItemView::SingleSelection);
    this->attendedEventsListW->setSelectionBehavior(QAbstractItemView::SelectRows);
    attendedEventsListW->setStyleSheet("QListWidget::item:selected { background-color: #87CEFA; }");


    this->populateAttendedList();

    listLayout->addWidget(title);
    listLayout->addWidget(attendedEventsListW);

    layout->addLayout(listLayout);
    layout->addLayout(createUserOperationsLayout());

    userScreen->setLayout(layout);
    stackedLayout->addWidget(userScreen);
}

void mainwindow::setupChartUI() {
    /*
    if (this->chartScreen) {
        stackedLayout->removeWidget(chartScreen);
        delete chartScreen;
        chartScreen = nullptr;
    }
    */

    this->chartScreen = new QWidget{};
    QVBoxLayout* layout = new QVBoxLayout{ chartScreen };

    std::vector<Event> allEvents = service.displayEventsService();
    std::vector<int> eventsPerMonth(12, 0);
    Utils u;
    for (const auto& e : allEvents) {
        try {
            std::string dateStr = e.getDate();
            int month = std::stoi(u.tokenize(dateStr, '-')[1]);
            if (month >= 1 && month <= 12)
                eventsPerMonth[month - 1]++;
        }
        catch (...) {}
    }

    BarChartWidget* chart = new BarChartWidget(eventsPerMonth);
    chart->setMinimumHeight(300);
    layout->addWidget(chart);

    QPushButton* backButton = new QPushButton("Back");
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(adminScreen);
        });
    layout->addWidget(backButton);
    stackedLayout->addWidget(chartScreen);
}

QVBoxLayout* mainwindow::createChooseMonthLayout() {
    QVBoxLayout* mainLayout = new QVBoxLayout{};
    QFormLayout* formLayout = new QFormLayout{};
    QFont font, titleFont;
    font.setPointSize(16);
    font.setBold(true);
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    QLabel* title = new QLabel{ "Choose the month:" };
    QLabel* description = new QLabel{ "Leave empty if you want all months" };
    QLabel* monthLabel = new QLabel{ "Month:" };
    QFont font2;
    font2.setPointSize(14);
    monthLabel->setFont(font);
    description->setFont(font);
    description->setAlignment(Qt::AlignCenter);
    this->chooseMonthLE = new QLineEdit();
    this->eventsInMonth = this->service.getEventsOnGivenMonth(-1);
    formLayout->addRow(monthLabel, this->chooseMonthLE);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    QPushButton* chooseButton = new QPushButton{ "Choose" };
    QPushButton* backButton = new QPushButton{ "Back" };
    connect(backButton, &QPushButton::clicked, [this]() {
        this->stackedLayout->setCurrentWidget(userScreen);
        });

    connect(chooseButton, &QPushButton::clicked, this, &mainwindow::handleSeeEventsButton);
    chooseButton->setFont(font);
    backButton->setFont(font);

    mainLayout->addWidget(title);
    mainLayout->addWidget(description);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(chooseButton);
    mainLayout->addWidget(backButton);

    return mainLayout;
}

QVBoxLayout* mainwindow::createChooseUserOrAdminMenuLayout() {
    QVBoxLayout* mainLayout = new QVBoxLayout{};
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    QLabel* title = new QLabel{ "Choose what you are:" };
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    QPushButton* adminMenu = new QPushButton{ "Admin" };
    QPushButton* userMenu = new QPushButton{ "User" };
    adminMenu->setFont(font);
    userMenu->setFont(font);
    adminMenu->setMinimumWidth(200);
    userMenu->setMinimumWidth(200);
    mainLayout->addWidget(title);
    mainLayout->addWidget(adminMenu);
    mainLayout->addWidget(userMenu);
    connect(adminMenu, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(adminScreen);
        });
    connect(userMenu, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(userScreen);
        });
    return mainLayout;
}

QVBoxLayout* mainwindow::createAdminOperationsLayout() {
    /*
        To fix:
        When entering the screen, the first element in the QList is selcted
        even though it doesn't show. Make it so that, by default, no element is selected.
    */
    QVBoxLayout* mainLayout = new QVBoxLayout{};
    QFormLayout* formLayout = new QFormLayout{};
    QLabel* titleLabel = new QLabel{ "Title" };
    QLabel* descriptionLabel = new QLabel{ "Description" };
    QLabel* dateLabel = new QLabel{ "Date" };
    QLabel* timeLabel = new QLabel{ "Time" };
    QLabel* numberOfPeopleLabel = new QLabel{ "Number of people" };
    QLabel* onlineLinkLabel = new QLabel{ "Online Link" };
    QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
    QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

    this->titleLE = new QLineEdit();
    this->descriptionLE = new QLineEdit();
    this->dateLE = new QLineEdit();
    this->timeLE = new QLineEdit();
    this->numberOfPeopleLE = new QLineEdit();
    this->linkLE = new QLineEdit();
    formLayout->addRow(titleLabel, titleLE);
    formLayout->addRow(descriptionLabel, descriptionLE);
    formLayout->addRow(dateLabel, dateLE);
    formLayout->addRow(timeLabel, timeLE);
    formLayout->addRow(numberOfPeopleLabel, numberOfPeopleLE);
    formLayout->addRow(onlineLinkLabel, linkLE);
    mainLayout->addLayout(formLayout);

    QPushButton* addButton = new QPushButton{ "Add" };
    connect(addButton, &QPushButton::clicked, this, &mainwindow::handleAddButton);
    QPushButton* removeButton = new QPushButton{ "Remove" };
    connect(removeButton, &QPushButton::clicked, this, &mainwindow::handleRemoveButton);
    QPushButton* updateButton = new QPushButton{ "Update" };
    connect(updateButton, &QPushButton::clicked, this, &mainwindow::handleUpdateButton);
    QPushButton* undoButton = new QPushButton{ "Undo" };
    connect(undoButton, &QPushButton::clicked, this, &mainwindow::handleUndoButton);
    QPushButton* redoButton = new QPushButton{ "Redo" };
    connect(redoButton, &QPushButton::clicked, this, &mainwindow::handleRedoButton);
    QPushButton* backButton = new QPushButton{ "Back" };
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(startScreen);
        });
    QPushButton* chartButton = new QPushButton{ "Show Events Chart" };
    connect(chartButton, &QPushButton::clicked, [this]() {
        this->setupChartUI();
        stackedLayout->setCurrentWidget(chartScreen);
        });
    connect(undoShortcut, &QShortcut::activated, this, &mainwindow::handleUndoButton);
    connect(redoShortcut, &QShortcut::activated, this, &mainwindow::handleRedoButton);
    mainLayout->addWidget(addButton);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(updateButton);
    mainLayout->addWidget(chartButton);
    mainLayout->addWidget(undoButton);
    mainLayout->addWidget(redoButton);
    mainLayout->addWidget(backButton);
    return mainLayout;
}

QVBoxLayout* mainwindow::createUserOperationsLayout() {
    QVBoxLayout* mainLayout = new QVBoxLayout{};
    QFont font;
    font.setPointSize(10);
    QPushButton* seeEventsButton = new QPushButton{ "See Events" };
    QPushButton* deleteEventButton = new QPushButton{ "Delete Event" };
    QPushButton* openInExternalAppButton = new QPushButton{ "Open in External App" };
    QPushButton* backButton = new QPushButton{ "Back" };
    QPushButton* tableButton = new QPushButton{ "Table View" };
    seeEventsButton->setFont(font);
    deleteEventButton->setFont(font);
    openInExternalAppButton->setFont(font);
    backButton->setFont(font);
    connect(backButton, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(startScreen);
        });
    mainLayout->addWidget(seeEventsButton);
    connect(seeEventsButton, &QPushButton::clicked, [this]() {
        stackedLayout->setCurrentWidget(chooseMonthScreen);
        });

    connect(deleteEventButton, &QPushButton::clicked, this, &mainwindow::handleDeleteFromAttendedButton);

    mainLayout->addWidget(deleteEventButton);
    mainLayout->addWidget(openInExternalAppButton);
    mainLayout->addWidget(tableButton);
    connect(tableButton, &QPushButton::clicked, this, &mainwindow::handleTableButton);
    connect(openInExternalAppButton, &QPushButton::clicked, [this]() {
        this->service.openInAppService();
        });
    mainLayout->addWidget(backButton);
    return mainLayout;
}

QVBoxLayout* mainwindow::createUserSlideshowLayout() {
    QVBoxLayout* mainLayout = new QVBoxLayout{};

    this->currentEventIndex = 0;
    this->displayedEventLabel = new QLabel{};
    this->updateDisplayedEvent();
    displayedEventLabel->setAlignment(Qt::AlignCenter);
    QFont font;
    font.setPointSize(12);
    font.setBold(true);
    this->displayedEventLabel->setFont(font);

    mainLayout->addWidget(this->displayedEventLabel);

    QPushButton* nextButton = new QPushButton{ "Next" };
    QPushButton* attendButton = new QPushButton{ "Attend" };
    QPushButton* openInBrowserButton = new QPushButton{ "Open in browser" };
    QPushButton* exitButton = new QPushButton{ "Exit slideshow" };

    connect(nextButton, &QPushButton::clicked, [this]() {
        if (this->currentEventIndex == this->eventsInMonth.size() - 1)
            this->currentEventIndex = 0;
        else this->currentEventIndex++;
        this->updateDisplayedEvent();
        });

    connect(attendButton, &QPushButton::clicked, [this]() {
        try {
            this->service.addEventToUserList(this->eventsInMonth[this->currentEventIndex]);
            this->populateAttendedList();
        }
        catch (DuplicateEventException& err) {
            QMessageBox::warning(this, "Error in attending!", "Event already attended!");
            return;
        }
        });

    connect(openInBrowserButton, &QPushButton::clicked, [this]() {
        this->service.openEventInBrowser(this->eventsInMonth[this->currentEventIndex]);
        });

    connect(exitButton, &QPushButton::clicked, [this]() {
        this->stackedLayout->setCurrentWidget(userScreen);
        });

    mainLayout->addWidget(this->displayedEventLabel);
    mainLayout->addWidget(nextButton);
    mainLayout->addWidget(attendButton);
    mainLayout->addWidget(openInBrowserButton);
    mainLayout->addWidget(exitButton);

    return mainLayout;
}

void mainwindow::handleAddButton() {
    try {
        std::string title = this->titleLE->text().toStdString();
        std::string description = this->descriptionLE->text().toStdString();
        std::string date = this->dateLE->text().toStdString();
        std::string time = this->timeLE->text().toStdString();
        std::string online_link = this->linkLE->text().toStdString();
        EventValidator::validateEventIdentifiers(title, description, date, time, this->numberOfPeopleLE->text().toStdString(), online_link);
        int numberOfPeople = std::stoi(this->numberOfPeopleLE->text().toStdString());
        service.addEventService(Event(title, description, date, time, numberOfPeople, online_link));
        this->populateList();
    }
    catch (EventExceptions& err) {
        QMessageBox* msgBox = new QMessageBox{};
        msgBox->setWindowTitle("Error in adding event!");
        std::string fullMessage = "";
        for (auto& e : err.returnErrors()) {
            fullMessage = fullMessage + e.what();
            fullMessage += "\n";
        }
        msgBox->setText(fullMessage.c_str());
        msgBox->exec();
    }
    catch (DuplicateEventException& err) {
        QMessageBox* msgBox = new QMessageBox{};
        msgBox->setWindowTitle("Error in adding event!");
        std::string fullMessage = "Error: ";
        fullMessage += err.what();
        msgBox->setText(fullMessage.c_str());
        msgBox->exec();
    }
}

QVBoxLayout* mainwindow::createChooseEventListTypeLayout() {
    QVBoxLayout* mainLayout = new QVBoxLayout{};
    QFont font;
    font.setPointSize(16);
    font.setBold(true);
    QLabel* title = new QLabel{ "Choose event list type:" };
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    QPushButton* csvButton = new QPushButton{ "CSV" };
    QPushButton* htmlButton = new QPushButton{ "HTML" };
    csvButton->setFont(font);
    htmlButton->setFont(font);
    csvButton->setMinimumWidth(200);
    htmlButton->setMinimumWidth(200);
    mainLayout->addWidget(title);
    mainLayout->addWidget(csvButton);
    mainLayout->addWidget(htmlButton);
    connect(csvButton, &QPushButton::clicked, [this]() {
        this->service.setEventListType(1);
        stackedLayout->setCurrentWidget(startScreen);
        });
    connect(htmlButton, &QPushButton::clicked, [this]() {
        this->service.setEventListType(2);
        stackedLayout->setCurrentWidget(startScreen);
        });
    return mainLayout;
}

void mainwindow::populateList() {
    std::vector<Event> events = this->service.displayEventsService();
    this->eventsListW->clear();
    for (int i = 0; i < events.size(); i++) {
        std::stringstream stream;
        stream << events[i];
        new QListWidgetItem(tr(stream.str().c_str()), eventsListW);
    }

}

void mainwindow::handleRemoveButton() {
    /*
    try {
        this->service.removeEventService(Event("", "", "", "", 0, this->linkLE->text().toStdString()));
    }
    catch (std::exception& e) {

    }
    this->populateList();
    */
    QListWidgetItem* selectedItem = eventsListW->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No selection", "Please select an event to remove from the list.");
        return;
    }
    try {
        Utils u;
        std::string originalText = selectedItem->text().toStdString();
        std::string link = u.tokenize(originalText, ',').back();
        this->service.removeEventService(Event("", "", "", "", 0, link));
        this->populateList();
    }
    catch (std::exception& e) {
        QMessageBox* msgBox = new QMessageBox{};
        msgBox->setWindowTitle("Error on removal");
        msgBox->setText(e.what());
        msgBox->exec();
    }
}

void mainwindow::handleUpdateButton() {
    QListWidgetItem* selectedItem = eventsListW->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No selection", "Please select an event to update from the list.");
        return;
    }
    try {
        Utils u;
        std::string originalText = selectedItem->text().toStdString();
        std::string oldlink = u.tokenize(originalText, ',').back();
        std::string title = this->titleLE->text().toStdString();
        std::string description = this->descriptionLE->text().toStdString();
        std::string date = this->dateLE->text().toStdString();
        std::string time = this->timeLE->text().toStdString();
        std::string online_link = this->linkLE->text().toStdString();
        EventValidator::validateEventIdentifiers(title, description, date, time, this->numberOfPeopleLE->text().toStdString(), online_link);
        int numberOfPeople = std::stoi(this->numberOfPeopleLE->text().toStdString());
        this->service.updateEventService(Event("", "", "", "", 0, oldlink), title, description, date, time, numberOfPeople, online_link);
        this->populateList();
    }
    catch (EventExceptions& err) {
        QMessageBox* msgBox = new QMessageBox{};
        msgBox->setWindowTitle("Error in adding event!");
        std::string fullMessage = "";
        for (auto& e : err.returnErrors()) {
            fullMessage = fullMessage + e.what();
            fullMessage += "\n";
        }
        msgBox->setText(fullMessage.c_str());
        msgBox->exec();
    }
    catch (DuplicateEventException& err) {
        QMessageBox* msgBox = new QMessageBox{};
        msgBox->setWindowTitle("Error in adding event!");
        std::string fullMessage = "Error: ";
        fullMessage += err.what();
        msgBox->setText(fullMessage.c_str());
        msgBox->exec();
    }
    catch (std::exception e) {
        QMessageBox* messageBox = new QMessageBox{};
        messageBox->setWindowTitle("Error when updating");
        messageBox->setText(e.what());
        messageBox->exec();
    }
}

void mainwindow::populateAttendedList() {
    std::vector<Event> attended = this->service.getEventInUserList();
    this->attendedEventsListW->clear();
    for (int i = 0; i < attended.size(); i++) {
        std::stringstream stream;
        stream << attended[i];
        new QListWidgetItem(tr(stream.str().c_str()), attendedEventsListW);
    }
}

void mainwindow::updateDisplayedEvent() {
    std::stringstream ss;
    ss << "Title: " << eventsInMonth[currentEventIndex].getTitle() << "\n"
        << "Description: " << eventsInMonth[currentEventIndex].getDescription() << "\n"
        << "Date: " << eventsInMonth[currentEventIndex].getDate() << "\n"
        << "Time: " << eventsInMonth[currentEventIndex].getTime() << "\n"
        << "Participants: " << eventsInMonth[currentEventIndex].getNumberOfPeople() << "\n"
        << "Link: " << eventsInMonth[currentEventIndex].getOnlineLink();
    this->displayedEventLabel->setText(QString::fromStdString(ss.str()));
}

void mainwindow::handleSeeEventsButton() {
    if (!chooseMonthLE) {
        QMessageBox::critical(this, "Internal Error", "Month input field was not initialized.");
        return;
    }
    std::string monthString = this->chooseMonthLE->text().toStdString();
    if (monthString.size() == 0) {
        this->eventsInMonth = this->service.getEventsOnGivenMonth(-1);
        this->currentEventIndex = 0;
        this->updateDisplayedEvent();
    }
    else {
        int monthInt = std::stoi(monthString);
        if (monthInt < 1 || monthInt > 12) {
            QMessageBox* msgBox = new QMessageBox{};
            msgBox->setWindowTitle("Error in month input!");
            msgBox->setText("Input a valid month (From 1 to 12)");
            msgBox->exec();
            return;
        }
        else {
            std::vector<Event> aux = this->service.getEventsOnGivenMonth(monthInt);
            if (aux.size() == 0) {
                QMessageBox* msgBox = new QMessageBox{};
                msgBox->setWindowTitle("Error in month input!");
                msgBox->setText("No event in this month!");
                msgBox->exec();
                return;
            }
            else {
                this->eventsInMonth = aux;
                this->currentEventIndex = 0;
                this->updateDisplayedEvent();
            }

        }
    }
    this->stackedLayout->setCurrentWidget(this->userSlideShowScreen);
}

void mainwindow::handleDeleteFromAttendedButton() {
    QListWidgetItem* selectedItem = attendedEventsListW->currentItem();
    if (!selectedItem) {
        QMessageBox::warning(this, "No selection", "Please select an event to remove from the list.");
        return;
    }
    Utils u;
    std::string link = u.tokenize(selectedItem->text().toStdString(), ',').back();
    this->service.deleteEventFromUserList(Event("", "", "", "", 0, link));
    this->populateAttendedList();
}

void mainwindow::handleUndoButton() {
    try {
        this->service.undoService();
        this->populateList();
    }
    catch (std::exception& err) {
        QMessageBox::warning(this, "Undo error", QString(err.what()));
    }
}

void mainwindow::handleRedoButton() {
    try {
        this->service.redoService();
        this->populateList();
    }
    catch (std::exception& err) {
        QMessageBox::warning(this, "Redo error", QString(err.what()));
    }
}

void mainwindow::handleTableButton() {
    AttendedTableDialog* dialog = new AttendedTableDialog(service, this);
    dialog->exec();
}

mainwindow::~mainwindow()
{
}
