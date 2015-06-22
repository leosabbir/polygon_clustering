#include "polygonsintersectionfinder.h"
typedef Polygon::Vertex_iterator Vertex_iterator;

PolygonsIntersectionFinder::PolygonsIntersectionFinder()
{

}

bool PolygonsIntersectionFinder::doIntersect(CustomPolygon p, CustomPolygon q) {
    Polygon_2 T1;
    //T1.push_back (Point_2 (1 , 1 ) );
    //T1.push_back (Point_2 (4 , 1 ) );
    //T1.push_back (Point_2 (1 , 3 ) );
    for (Vertex_iterator iter = p.vertices_begin(); iter != p.vertices_end(); iter++) {
        double x = CGAL::to_double((*iter).x());
        double y = CGAL::to_double((*iter).y());
        T1.push_back(Point_2(x, y));
    }

    //Line_2 T2(Point_2 (10 , 10 ), Point_2 (15 , 1 ) );
    Polygon_2 T2;
    //T2.push_back (Point_2 (10 , 10 ) );
    //T2.push_back (Point_2 (15 , 1 ) );
    //T2.push_back (Point_2 (10 , 15 ) );
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

    //Polygon_set_2 ps;
    //ps.insert(T1);

    //return ps.do_intersect(T2);
    if (T2.is_clockwise_oriented()){
        T2.reverse_orientation();
    }
    return CGAL::do_intersect(T1, T2);
}
