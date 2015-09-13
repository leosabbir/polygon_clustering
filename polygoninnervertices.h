#ifndef POLYGONINNERVERTICES_H
#define POLYGONINNERVERTICES_H

#include <QMap>
#include <QList>
#include "custompoint.h"

class PolygonInnerVertices {

public:
    PolygonInnerVertices();

private:
    QMap<int, QList<CustomPoint>> *polygonVertices;
};

#endif // POLYGONINNERVERTICES_H
