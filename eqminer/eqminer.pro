######################################################################
# Automatically generated by qmake (3.1) Mon Nov 7 09:54:08 2022
######################################################################

QT+=widgets
TEMPLATE = app
TARGET = eqminer
INCLUDEPATH += .

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += myconfig.h randomio.h ui_widget.h widget.h
FORMS += widget.ui
SOURCES += main.cpp myconfig.cpp randomio.cpp widget.cpp
