#ifndef CUSTOMPOLYGON_H
#define CUSTOMPOLYGON_H

#include "customeline.h"
#include <QList>

#include <CGAL/Homogeneous.h>
#include <CGAL/Polytope_distance_d.h>
#include <CGAL/Polytope_distance_d_traits_2.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::MP_Float ET;

typedef CGAL::Homogeneous<ET> K;
typedef CGAL::Polygon_2<K> Polygon;

typedef CGAL::Polytope_distance_d_traits_2<K> Traits;
typedef CGAL::Polytope_distance_d<Traits>     Polytope_distance;


class CustomPolygon : public Polygon {

public:
    CustomPolygon();
    void addConnectingPolygon(int polygonIndex, CustomeLine line);
    bool hasConnectingPolygons();
    CustomeLine computeDistance(CustomPolygon p) const;
    bool doIntersect(CustomPolygon p) const;
    CustomPoint* getVertices() const;

private:
    QList<int> connectedPolygons;
    QList<CustomeLine> connectingLines;
};

#endif // CUSTOMPOLYGON_H
