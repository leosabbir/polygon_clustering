#ifndef POLYGONSINTERSECTIONFINDER_H
#define POLYGONSINTERSECTIONFINDER_H

#include "custompolygon.h"
#include "CGAL/Polygon_set_2.h"
#include "CGAL/Boolean_set_operations_2.h"

#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2 Point_2;
typedef CGAL::Line_2<Kernel> Line_2;
typedef CGAL::Polygon_2<Kernel> Polygon_2 ;
//typedef CGAL::Polygon_set_2<Kernel, std::vector<Point_2> > Polygon_set_2;

class PolygonsIntersectionFinder
{
public:
    PolygonsIntersectionFinder();
    bool doIntersect(CustomPolygon p, CustomPolygon q);
};

#endif // POLYGONSINTERSECTIONFINDER_H
