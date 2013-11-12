#-------------------------------------------------
#
# Project created by QtCreator 2013-11-11T18:36:22
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WSChat
TEMPLATE = app


SOURCES += main.cpp \
        WSChat.cpp \
        QWebSocket_files/functions.cpp \
        QWebSocket_files/QTlsServer.cpp \
        QWebSocket_files/QWsFrame.cpp \
        QWebSocket_files/QWsHandshake.cpp \
        QWebSocket_files/QWsServer.cpp \
        QWebSocket_files/QWsSocket.cpp \
    LoginDlg.cpp

HEADERS  += WSChat.h \
    QWebSocket_files/functions.h \
    QWebSocket_files/QTlsServer.h \
    QWebSocket_files/QWsFrame.h \
    QWebSocket_files/QWsHandshake.h \
    QWebSocket_files/QWsServer.h \
    QWebSocket_files/QWsSocket.h \
    QWebSocket_files/WsEnums.h \
    LoginDlg.h


FORMS    += WSChat.ui \
    LoginDlg.ui
