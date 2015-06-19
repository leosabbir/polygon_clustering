#ifndef CUSTOMPOINT_H
#define CUSTOMPOINT_H

#include <CGAL/Homogeneous.h>
#include <CGAL/MP_Float.h>
typedef CGAL::MP_Float ET;

typedef CGAL::Homogeneous<ET> K;
typedef K::Point_2            Point;

class CustomPoint : public Point {

public:
    CustomPoint(double x, double y);

};

#endif // CUSTOMPOINT_H
