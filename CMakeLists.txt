﻿cmake_minimum_required(VERSION 3.5)

project(QtTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        widget.cpp
        widget.h
        widget.ui
        flatui.h flatui.cpp
        qcustomplot.h qcustomplot.cpp
        readcsvfile.h readcsvfile.cpp
        gmsh.h
        generatemesh.h generatemesh.cpp
        computecontactstress.h computecontactstress.cpp
)


if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtTest
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
endif()

target_include_directories(QtTest PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(QtTest PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(QtTest PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

if (WIN32)
    target_link_libraries(QtTest PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/gmsh-4.11.dll)
elseif (UNIX)
    target_link_libraries(QtTest PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/libgmsh.so)
endif()

set_target_properties(QtTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER Meng
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS QtTest
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtTest)
endif()
