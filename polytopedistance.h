#ifndef POLYTOPEDISTANCE_H
#define POLYTOPEDISTANCE_H

#include <iostream>
#include <cassert>
#include <CGAL/Homogeneous.h>
#include <CGAL/Polytope_distance_d.h>
#include <CGAL/Polytope_distance_d_traits_2.h>

//#ifdef CGAL_USE_GMP
//#include <CGAL/Gmpzf.h>
//typedef CGAL::Gmpzf ET;
//#else
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;
//#endif
// use an EXACT kernel...
typedef CGAL::Homogeneous<ET>                 K;
typedef K::Point_2                           Point;
// ...and the traits class based on the exact kernel
typedef CGAL::Polytope_distance_d_traits_2<K> Traits;
typedef CGAL::Polytope_distance_d<Traits>     Polytope_distance;


class PolytopeDistance
{
public:
    PolytopeDistance();
    int computeDistance();
};

#endif // POLYTOPEDISTANCE_H
