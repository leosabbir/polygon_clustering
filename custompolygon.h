#ifndef CUSTOMPOLYGON_H
#define CUSTOMPOLYGON_H

#include "customeline.h"
#include "utils.h"
#include "constants.h"
#include <QList>
#include <QDebug>

#include <CGAL/Homogeneous.h>
#include <CGAL/Polytope_distance_d.h>
#include <CGAL/Polytope_distance_d_traits_2.h>
#include <CGAL/MP_Float.h>
#include <CGAL/Polygon_2.h>

typedef CGAL::MP_Float ET;

typedef CGAL::Homogeneous<ET> K;
typedef CGAL::Polygon_2<K> Polygon;
typedef CGAL::Point_2<K> Point;

typedef CGAL::Polytope_distance_d_traits_2<K> Traits;
typedef CGAL::Polytope_distance_d<Traits>     Polytope_distance;
typedef Polygon::Vertex_iterator Vertex_iterator;


class CustomPolygon : public Polygon {

public:
    CustomPolygon();
    void addConnectingPolygon(int polygonIndex, CustomeLine line);
    bool hasConnectingPolygons();
    CustomeLine* computeDistance(CustomPolygon p) const;
    bool doIntersect(CustomPolygon p) const;
    CustomPoint* getVertices() const;
    int hasVertex(double x, double y);
    bool isSelected;

private:
    QList<int> connectedPolygons;
    QList<CustomeLine> connectingLines;
};

#endif // CUSTOMPOLYGON_H
