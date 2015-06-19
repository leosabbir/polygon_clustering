#include "customeline.h"

CustomeLine::CustomeLine(Point p, Point q) {
    this-> p = p;
    this-> q = q;
    this-> length = 0;
}

CustomeLine::CustomeLine(Point p, Point q, double length) {
    this-> p = p;
    this-> q = q;
    this-> length = length;
}

Point CustomeLine::getP() {
    return this -> p;
}

Point CustomeLine::getQ() {
    return this -> q;
}

double CustomeLine::getDistance() {
    return this->length;
}
