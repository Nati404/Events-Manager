#pragma once

#include "ui_mainwindowClass.h"
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QLabel>
#include "service/Service.h"

class mainwindow : public QWidget
{
    Q_OBJECT

public:
    mainwindow();
    ~mainwindow();

private:
    Service service;
    Ui::mainwindowClass ui;
    QStackedLayout* stackedLayout;
    QWidget* startScreen;
    QWidget* adminScreen;
    QWidget* userScreen;
    QWidget* chooseRepoTypeScreen;
    QWidget* chooseEventListTypeScreen;
    QWidget* chooseMonthScreen;
    QWidget* userSlideShowScreen;
    QWidget* chartScreen;

    QListWidget* eventsListW;
    QListWidget* attendedEventsListW;
    QLineEdit* titleLE;
    QLineEdit* descriptionLE;
    QLineEdit* dateLE;
    QLineEdit* timeLE;
    QLineEdit* numberOfPeopleLE;
    QLineEdit* linkLE;
    QLineEdit* chooseMonthLE;
    QLabel* displayedEventLabel;

    int currentEventIndex = 0;
    std::vector<Event> eventsInMonth;

    void setupStartingUI();
    void setupAdminUI();
    void setupUserUI();
    void setupEventListTypeUI();
    void setupChooseMonthUI();
    void setupEventSlideshowUI();
    void setupChartUI();
    void updateDisplayedEvent();
    void populateList();
    void populateAttendedList();
    QVBoxLayout* createAdminOperationsLayout();
    QVBoxLayout* createChooseUserOrAdminMenuLayout();
    QVBoxLayout* createUserOperationsLayout();
    QVBoxLayout* createChooseEventListTypeLayout();
    QVBoxLayout* createChooseMonthLayout();
    QVBoxLayout* createUserSlideshowLayout();
    void handleAddButton();
    void handleRemoveButton();
    void handleUpdateButton();
    void handleSeeEventsButton();
    void handleDeleteFromAttendedButton();
    void handleUndoButton();
    void handleRedoButton();
    void handleTableButton();
};

