#ifndef DUMMYDATA_H
#define DUMMYDATA_H

#include <QList>
#include <QPoint>


class DummyData
{
    private:
        QList<QList<QPoint> > polygons;

    public:
        DummyData();
        QList<QList<QPoint> > getPolygons();



};

#endif // DUMMYDATA_H
