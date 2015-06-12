#include "dummydata.h"

DummyData::DummyData()
{
    QList<QPoint> polygon;

    polygon << QPoint(10,60) <<  QPoint(50,65) << QPoint(55,105) << QPoint(60,65) << QPoint(100,60) << QPoint(60,55)
            << QPoint(55,15) << QPoint(50,55) << QPoint(10,60);

    this->polygons << polygon;

    polygon = *(new QList<QPoint>);
    polygon << QPoint(100,10) <<  QPoint(110,100) << QPoint(120,40) << QPoint(150, 35);// << QPoint(100,30) << QPoint(60,5);
    this->polygons << polygon;

    polygon = *(new QList<QPoint>);
    polygon << QPoint(200,10) <<  QPoint(190,300) << QPoint(600,150) << QPoint(350, 35);// << QPoint(100,30) << QPoint(60,5);
    this->polygons << polygon;

    polygon = *(new QList<QPoint>);
    polygon << QPoint(770,525) <<  QPoint(750, 560) << QPoint(600,550);// << QPoint(100,30) << QPoint(60,5);
    this->polygons << polygon;

    polygon = *(new QList<QPoint>);
    polygon << QPoint(30,550) <<  QPoint(60, 400) << QPoint(200,370) << QPoint(300,400) << QPoint(250,500);
    this->polygons << polygon;

    polygon = *(new QList<QPoint>);
    polygon << QPoint(400,300) <<  QPoint(400, 450) << QPoint(420,520) << QPoint(440,480) << QPoint(650,500) << QPoint(600,400);
    this->polygons << polygon;
}

QList< QList<QPoint> > DummyData::getPolygons() {
    return this->polygons;
}

