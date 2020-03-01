#-------------------------------------------------
#
# Project created by QtCreator 2019-12-17T15:36:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ToolButtonWidget
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    form.cpp \
    subDialog.cpp \
    widget.cpp \
    BtnWidget.cpp

HEADERS  += dialog.h \
    datatype.h \
    form.h \
    subDialog.h \
    widget.h \
    BtnWidget.h

FORMS    += dialog.ui \
    form.ui \
    subDialog.ui \
    widget.ui \
    BtnWidget.ui
