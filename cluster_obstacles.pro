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
    mainstage.cpp \
    polytopedistance.cpp \
    custompoint.cpp \
    customeline.cpp \
    custompolygon.cpp \
    polygoncomputationutil.cpp \
    polygonindexlinepair.cpp \
    inputfilereader.cpp \
    context.cpp \
    polygonsintersectionfinder.cpp

HEADERS  += mainwindow.h \
            glwidget.h \
    dummydata.h \
    plygoncontainer.h \
    mainstage.h \
    polytopedistance.h \
    custompoint.h \
    customeline.h \
    custompolygon.h \
    polygoncomputationutil.h \
    polygonindexlinepair.h \
    inputfilereader.h \
    context.h \
    polygonsintersectionfinder.h

INCLUDEPATH +=   /usr/local/include/
LIBS        += -L/usr/local/include/
LIBS        += -lCGAL
LIBS        += -lgmp
LIBS        += -lmpfr
LIBS        += -lglut
LIBS        += -DBOOST_LOG_DYN_LINK
LIBS        += -lboost_thread
LIBS        += -lpthread
QMAKE_CXXFLAGS += -frounding-math -O3

FORMS    += mainwindow.ui \
    plygoncontainer.ui

RESOURCES += \
    resources/resources.qrc
