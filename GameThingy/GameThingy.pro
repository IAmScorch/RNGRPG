#-------------------------------------------------
#
# Project created by QtCreator 2014-08-18T18:48:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = GameThingy
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
    player.cpp \
    bandit.cpp \
    warrior.cpp \
    gamelogic.cpp \
    quests.cpp

HEADERS  += gamelogic.h \
    player.h \
    bandit.h \
    warrior.h \
    quests.h

FORMS    += IntroMenu.ui
