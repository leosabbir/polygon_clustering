#ifndef VDUTIL_H
#define VDUTIL_H

#include <QList>
#include "custompoint.h"

#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Delaunay_triangulation_2.h>
#include <iterator>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K2;
typedef K2::Point_2 Point_2_Voronoi;
typedef K2::Iso_rectangle_2 Iso_rectangle_2;
typedef K2::Segment_2 Segment_2;
typedef K2::Ray_2 Ray_2;
typedef K2::Line_2 Line_2_Voronoi;
typedef CGAL::Delaunay_triangulation_2<K2>  Delaunay_triangulation_2;
class VDUtil
{
public:
    VDUtil();

    //void printEndPoint(Halfedge_handle e, bool isSrc);
    void construct(QList<CustomPoint> vertices);
    void construct2(QList<CustomPoint> vertices);
    QList<CustomPoint> getVoronoiLineSegments();

private:
    QList<CustomPoint>* voronoiLineSegments;
};

#endif // VDUTIL_H
