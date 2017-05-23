TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

#LIBS += `pkg-config --libs sfml-all` -static
#QMAKE_CXXFLAGS += -static
LIBS += -lsfml-system
LIBS += -lsfml-graphics
LIBS += -lsfml-window
#LIBS += -lsfml-audio
#LIBS += -lsfml-network
QMAKE_CXXFLAGS += -std=gnu++14

