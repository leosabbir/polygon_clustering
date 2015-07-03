#include "mainwindow.h"
#include <QtGui>
#include <GL/glut.h>
#include <QApplication>
#include "polytopedistance.h"


//TODO if polygons intersects, compuation of distance will crash
// dont delete all vertices
// not convex polygons will give fautly distances




int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
}

