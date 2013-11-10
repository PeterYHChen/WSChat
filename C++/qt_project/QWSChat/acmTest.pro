#-------------------------------------------------
#
# Project created by QtCreator 2013-11-04T10:07:22
#
#-------------------------------------------------

QT       += core gui
QT       += network

TARGET = QWSChat
TEMPLATE = app


SOURCES += main.cpp\
    functions.cpp \
    QTlsServer.cpp \
    QWsFrame.cpp \
    QWsHandshake.cpp \
    QWsServer.cpp \
    QWsSocket.cpp \
    login.cpp \
    QWSChat.cpp

HEADERS  += \
    functions.h \
    QTlsServer.h \
    QWsFrame.h \
    QWsHandshake.h \
    QWsServer.h \
    QWsSocket.h \
    WsEnums.h \
    login.h \
    QWSChat.h

FORMS    += \
    login.ui \
    QWSChat.ui
