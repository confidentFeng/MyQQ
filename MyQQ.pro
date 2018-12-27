#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T09:51:55
#
#-------------------------------------------------

QT       += core gui
QT       += widgets
QT       += sql
QT       += network
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyQQ
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        qq.cpp \
    qqlogin.cpp \
    cregister.cpp \
    cimagechoose.cpp \
    ctalkwithdialog.cpp \
    cgroupitem.cpp \
    cgroupwidget.cpp \
    cpeople.cpp \
    menupushbutton.cpp \
    clookforpasswd.cpp

HEADERS  += qq.h \
    qqlogin.h \
    cregister.h \
    cimagechoose.h \
    ctalkwithdialog.h \
    cgroupitem.h \
    cgroupwidget.h \
    cpeople.h \
    menubutton.h \
    clookforpasswd.h

FORMS    += qq.ui \
    qqlogin.ui \
    cregister.ui \
    cimagechoose.ui \
    ctalkwithdialog.ui \
    clookforpasswd.ui

RESOURCES += \
    images.qrc

DISTFILES += \
    blue.qss
#国际化语言翻译
TRANSLATIONS = login_zh_CN.ts
#建立自己的图标
RC_ICONS = my.ico
#RC_ICONS = qlogo.png
