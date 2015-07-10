#include "polygonsintersectionfinder.h"
typedef Polygon::Vertex_iterator Vertex_iterator;

PolygonsIntersectionFinder::PolygonsIntersectionFinder()
{

}

bool PolygonsIntersectionFinder::doIntersect(CustomPolygon p, CustomPolygon q) {
    Polygon_2 T1;
    for (Vertex_iterator iter = p.vertices_begin(); iter != p.vertices_end(); iter++) {
        double x = CGAL::to_double((*iter).x());
        double y = CGAL::to_double((*iter).y());
        T1.push_back(Point_2(x, y));
    }

    Polygon_2 T2;
    double prev_x;
    int i = 0;
    for (Vertex_iterator iter = q.vertices_begin(); iter != q.vertices_end(); iter++) {
        double x = CGAL::to_double((*iter).x());
        double y = CGAL::to_double((*iter).y());
        T2.push_back(Point_2(x, y));
        if ( i == 1 ) {
            if ( prev_x == x) {
                x = x + 5;
            } else {
                y = y + 5;
            }
            T2.push_back(Point_2(x, y));
        }
        prev_x = x;
        i++;
    }

    if (T2.is_clockwise_oriented()){
        T2.reverse_orientation();
    }
    return CGAL::do_intersect(T1, T2);
}

bool PolygonsIntersectionFinder::isInside(CustomPolygon p, double x, double y) {
    switch (getPointLocationOnPolygon(p, x, y)) {
        case CGAL::ON_BOUNDED_SIDE:
            return true;
        case CGAL::ON_BOUNDARY:
            return true;
        default:
            return false;
    }

}

CGAL::Bounded_side PolygonsIntersectionFinder::getPointLocationOnPolygon(CustomPolygon p, double x, double y) {
    Point_2 points[p.size()];
    int i = 0;
    for (Vertex_iterator iter = p.vertices_begin(); iter != p.vertices_end(); iter++) {
        double x = CGAL::to_double((*iter).x());
        double y = CGAL::to_double((*iter).y());
        points[i++] = Point_2(x, y);
    }

    return CGAL::bounded_side_2(points, points + p.size(), Point_2(x, y), Kernel());
}


