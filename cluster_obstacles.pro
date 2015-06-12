#-------------------------------------------------
#
# Project created by QtCreator 2015-06-09T21:26:09
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cluster_obstacles
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        glwidget.cpp \
    dummydata.cpp \
    plygoncontainer.cpp \
    mainstage.cpp

HEADERS  += mainwindow.h \
            glwidget.h \
    dummydata.h \
    plygoncontainer.h \
    mainstage.h

INCLUDEPATH +=   /usr/include/
LIBS        += -L/usr/include/
LIBS        += -lCGAL
LIBS        += -lgmp
LIBS        += -lmpfr
LIBS        += -lglut
QMAKE_CXXFLAGS += -frounding-math -O3

FORMS    += mainwindow.ui \
    plygoncontainer.ui
