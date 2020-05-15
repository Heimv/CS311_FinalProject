cmake_minimum_required(VERSION 3.10)
project(FinalProject)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOGEN_VERBOSE 1)
set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_CXX_FLAGS "-Wall -std=c++17 -g")
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\mingw73_64\\lib\\cmake\\")
find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )

set(
        SOURCES
        src/main.cpp
        src/BinSearchSortTree/binstree.cpp
        src/Elem/elem.cpp
        src/GUI/mainWindow.cpp
        ui/mainWindow.ui
        src/Elem/generateId.cpp
        src/CSV/csvManager.cpp
        src/CSV/rapidcsv.h)
add_executable(
        FinalProject
        ${SOURCES}
        ${HEADERS}
)
target_link_libraries(FinalProject Qt5::Core Qt5::Widgets)
