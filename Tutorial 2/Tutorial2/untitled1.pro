TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

LIBS += `pkg-config --libs sfml-all`

QMAKE_CXXFLAGS += -std=gnu++14
