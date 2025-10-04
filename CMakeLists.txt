cmake_minimum_required(VERSION 3.5)

project(EventsManager)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

INCLUDE_DIRECTORIES(.)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)

add_executable(EventsManager
    main.cpp

    domain/Action.cpp
    domain/Event.cpp

    table/AttendedEventsTableModel.cpp
    table/AttendedTableDialog.cpp

    widgets/BarChartWidget.cpp

    eventlist/CsvEventList.cpp
    eventlist/FileEventList.cpp
    eventlist/HtmlEventList.cpp

    exceptions/Exceptions.cpp

    repository/FileRepository.cpp
    repository/Repository.cpp
    repository/UserRepository.cpp

    service/Service.cpp

    ui/UI.cpp

    utils/Utils.cpp

    validator/EventValidator.cpp

    mainwindow.cpp

    mainwindowClass.ui
)

target_link_libraries(EventsManager Qt::Core Qt::Gui Qt::Widgets)
