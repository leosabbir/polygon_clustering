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
    polytopedistance.cpp \
    custompoint.cpp \
    customeline.cpp \
    polygonsreadwriteutil.cpp \
    polygoninnervertices.cpp \
    custompolygon.cpp \
    polygoncomputationutil.cpp \
    context.cpp \
    polygonsintersectionfinder.cpp \
    constants.cpp \
    utils.cpp \
    weightedquickunionuf.cpp \
    convexhullcomputationutil.cpp \
    vdutil.cpp

HEADERS  += mainwindow.h \
            glwidget.h \
    dummydata.h \
    polytopedistance.h \
    custompoint.h \
    customeline.h \
    custompolygon.h \
    polygoncomputationutil.h \
    context.h \
    polygonsintersectionfinder.h \
    constants.h \
    utils.h \
    weightedquickunionuf.h \
    convexhullcomputationutil.h \
    polygonsreadwriteutil.h \
    polygoninnervertices.h \
    vdutil.h

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
QMAKE_CXXFLAGS += -std=c++11

FORMS    += mainwindow.ui

RESOURCES += \
    resources/resources.qrc
