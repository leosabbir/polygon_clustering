#ifndef CUSTOMELINE_H
#define CUSTOMELINE_H

#include "custompoint.h"

class CustomeLine {

public:
    CustomeLine(Point p, Point q);
    CustomeLine(Point p, Point q, double length);
    Point getP();
    Point getQ();
    double getDistance();

private:

    Point p;
    Point q;
    double length;
};

#endif // CUSTOMELINE_H
