######################################################################
# Automatically generated by qmake (3.1) Mon Nov 7 12:30:11 2022
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
HEADERS += filecontent.h myconfig.h mydir.h randomio.h ui_widget.h widget.h \
    confirmerwidget.h \
    equalfile.h
FORMS += widget.ui \
    confirmerwidget.ui
SOURCES += filecontent.cpp \
           confirmerwidget.cpp \
           main.cpp \
           myconfig.cpp \
           mydir.cpp \
           randomio.cpp \
           widget.cpp
