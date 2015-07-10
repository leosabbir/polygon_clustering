#ifndef CONVEXHULLCOMPUTATIONUTIL_H
#define CONVEXHULLCOMPUTATIONUTIL_H

#include <QList>
#include "custompolygon.h"

#include "weightedquickunionuf.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel KernelForConvexHull;
typedef KernelForConvexHull::Point_2 PointForConvexHull;

class ConvexHullComputationUtil
{
public:
    ConvexHullComputationUtil();

    void compute(QList<CustomPolygon> polygons, std::vector<std::vector<PointForConvexHull> > &results);
};

#endif // CONVEXHULLCOMPUTATIONUTIL_H
