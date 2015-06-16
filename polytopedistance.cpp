#include "polytopedistance.h"

PolytopeDistance::PolytopeDistance()
{

}

int PolytopeDistance::computeDistance() {
    // the cube [0,1]^3
      //Point P[4] = { Point(0,0), Point(0,1), Point(1,0), Point(1,1)};
      Point P[4] = { Point(0,0), Point(0,1), Point(1,0), Point(1,1)};
      // the cube [2,3]^3
      //Point Q[4] = { Point(3,2), Point(3,3), Point(4,2), Point(4,3)};
      //Point Q[3] = { Point(4,0), Point(0,4), Point(4,5)}; //passes through 2,2
      Point Q[3] = { Point(3,0), Point(0,3), Point(4,5)}; //passes through 1.5,1.5
      //Point Q[3] = { Point(0,3), Point(3,3), Point(4,5)};

      Polytope_distance pd(P, P+4, Q, Q+3);
      assert (pd.is_valid());
      // get squared distance (2,2,2)-(1,1,1))^2 = 3
      std::cout << "Squared distance: " <<
        CGAL::to_double (pd.squared_distance_numerator()) /
        CGAL::to_double (pd.squared_distance_denominator()) << std::endl;

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
              //x.div(factor);
              //y.div(factor);
              std::cout << "p: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) << std::endl;
          }
          i++;
      }

        i = 1;
      //std::cout << "q:"; // homogeneous point from second cube, (2,2,2,1)
      for (coord_it = pd.realizing_point_q_coordinates_begin();
           coord_it != pd.realizing_point_q_coordinates_end();
           ++coord_it) {
          if ( i % 3 == 1) {
              x = *coord_it;
          } else if (i % 3 == 2) {
              y = *coord_it;
          } else {
              CGAL::MP_Float factor = *coord_it;
              //x.div(factor);
              //y.div(factor);
              std::cout << "q: " << CGAL::to_double(x)/CGAL::to_double(factor) << ", " << CGAL::to_double(y)/CGAL::to_double(factor) <<std::endl;
          }
          i++;
      }
      std::cout << std::endl;
      return 0;
}

