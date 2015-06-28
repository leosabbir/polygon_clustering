#include "custompolygon.h"
#include "CGAL/Polygon_set_2.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <iostream>
#include "polygonsintersectionfinder.h"

typedef CGAL::Exact_predicates_exact_constructions_kernel Kernel;
typedef Kernel::Point_2                                   Point_2;
typedef CGAL::Polygon_2<Kernel>                           Polygon_2;
typedef CGAL::Polygon_set_2<K, std::vector<Point> > Polygon_set_2;

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
    //std::cout << this->size() << std::endl;
    CustomPoint* vertices = static_cast<CustomPoint*>(::operator new[](sizeof(CustomPoint) * this->size()));
    //CustomPoint* vertices = new CustomPoint[this->size()];
    //Object2* objArray = static_cast<Object2*>( ::operator new ( sizeof Object2 * NUM_OF_OBJS ) );
    //vertices = new CustomPoint[this->size()];
    for (Vertex_iterator iter = this->vertices_begin(); iter != this->vertices_end(); iter++) {
        //CustomPoint vertex(CGAL::to_double((*iter).x()), CGAL::to_double((*iter).y()));
        //std::cout << CGAL::to_double((*iter).x()) << ", " << CGAL::to_double((*iter).y());
        new(&vertices[i]) CustomPoint(CGAL::to_double((*iter).x()), CGAL::to_double((*iter).y()));
        //vertices[i] = *(new CustomPoint(CGAL::to_double((*iter).x()), CGAL::to_double((*iter).y())));
        i++;
    }
    //std::cout << std::endl;
    return vertices;
}

CustomeLine* CustomPolygon::computeDistance(CustomPolygon p) const {
    Point *pointP, *pointQ;

    CustomPoint *pointPs = this->getVertices();
    CustomPoint *pointQs = p.getVertices();

    //Polytope_distance pd(pointPs, pointPs + sizeof(pointPs)/sizeof(*pointPs), pointQs, pointQs + sizeof(pointQs)/sizeof(*pointQs));
    Polytope_distance pd(pointPs, pointPs + this->size(), pointQs, pointQs + p.size());
    assert (pd.is_valid());

    double distance = CGAL::to_double (pd.squared_distance_numerator()) /
      CGAL::to_double (pd.squared_distance_denominator());
    //std::cout << "Distance: " << distance << std::endl;

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
            //std::cout << "p: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) << std::endl;
            pointP = new Point(CGAL::to_double(x)/CGAL::to_double(factor), CGAL::to_double(y)/CGAL::to_double(factor));
            break;
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
            //std::cout << "q: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) <<std::endl;
            pointQ = new Point(CGAL::to_double(x)/CGAL::to_double(factor), CGAL::to_double(y)/CGAL::to_double(factor));
            break;
        }
        i++;
    }
    return new CustomeLine(*pointP, *pointQ, distance);
}

bool CustomPolygon::doIntersect(CustomPolygon p) const {
    Polygon_set_2 ps;
    //ps->insert(*this);

    //return ps.do_intersect(p);
    PolygonsIntersectionFinder i;
    return i.doIntersect(*this, p);
    //return false;
}

