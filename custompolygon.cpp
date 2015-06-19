#include "custompolygon.h"
#include "CGAL/Polygon_set_2.h"

typedef CGAL::Polygon_set_2<K, std::vector<Point> > Polygon_set_2;
typedef Polygon::Vertex_iterator Vertex_iterator;

CustomPolygon::CustomPolygon() {

}

void CustomPolygon::addConnectingPolygon(int polygonIndex, CustomeLine line) {
    this->connectedPolygons.append(polygonIndex);
    this->connectingLines.append(line);
}

bool CustomPolygon::hasConnectingPolygons() {
    return this->connectedPolygons.size() > 0;
}

CustomPoint* CustomPolygon::getVertices() const {
    int i = 0;
    CustomPoint* vertices;
    for (Vertex_iterator iter = this->vertices_begin(); iter != this->vertices_end(); iter++) {
        CustomPoint vertex(CGAL::to_double((*iter).x()), CGAL::to_double((*iter).y()));
        vertices[i] = vertex;
        i++;
    }

    return vertices;
}

CustomeLine CustomPolygon::computeDistance(CustomPolygon p) const {
    Point *pointP, *pointQ;

    CustomPoint *pointPs = this->getVertices();
    CustomPoint *pointQs = p.getVertices();

    Polytope_distance pd(pointPs, pointPs + sizeof(pointPs)/sizeof(*pointPs), pointQs, pointQs + sizeof(pointQs)/sizeof(*pointQs));
    assert (pd.is_valid());

    double distance = CGAL::to_double (pd.squared_distance_numerator()) /
      CGAL::to_double (pd.squared_distance_denominator());

    // get points that realize the distance
    Polytope_distance::Coordinate_iterator  coord_it;

    CGAL::MP_Float x,y;
    int i = 1;
    for (coord_it = pd.realizing_point_p_coordinates_begin();
         coord_it != pd.realizing_point_p_coordinates_end();
         ++coord_it) {
        if ( i % 3 == 1) {
            x = *coord_it;
        } else if (i % 3 == 2) {
            y = *coord_it;
        } else {
            CGAL::MP_Float factor = *coord_it;
            std::cout << "p: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) << std::endl;
            *pointP = Point(CGAL::to_double(x)/CGAL::to_double(factor), CGAL::to_double(y)/CGAL::to_double(factor));
        }
        i++;
    }


    i = 1;
    for (coord_it = pd.realizing_point_q_coordinates_begin();
         coord_it != pd.realizing_point_q_coordinates_end();
         ++coord_it) {
        if ( i % 3 == 1) {
            x = *coord_it;
        } else if (i % 3 == 2) {
            y = *coord_it;
        } else {
            CGAL::MP_Float factor = *coord_it;
            std::cout << "q: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) <<std::endl;
            *pointQ = Point(CGAL::to_double(x)/CGAL::to_double(factor), CGAL::to_double(y)/CGAL::to_double(factor));
        }
        i++;
    }
    return CustomeLine(*pointP, *pointQ, distance);
}

bool CustomPolygon::doIntersect(CustomPolygon p) const {
    Polygon_set_2 ps;
    ps.insert(*this);

    return ps.do_intersect(p);
}

