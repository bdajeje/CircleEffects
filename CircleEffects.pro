TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -pthread \
        -lsfml-graphics -lsfml-window -lsfml-system \

SOURCES += main.cpp \
    graphics/drawable.cpp \
    graphics/circle.cpp \
    utils/timer.cpp \
    graphics/point.cpp

HEADERS += \
    graphics/drawable.hpp \
    graphics/circle.hpp \
    utils/timer.hpp \
    graphics/point.hpp
