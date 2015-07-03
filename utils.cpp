#include "utils.h"

Utils::Utils()
{

}

double Utils::transform(double coord, double total) {
    double transformed = (coord * 1.0 - total)/total;
    transformed = coord * 1.0 / total;
    return transformed * 2 - 1;
}

bool Utils::inBetween(double val, double val1, double val2) {
    if (val1 > val2) {
        return val >= val2 && val <= val1;
    } else {
        return val >= val1 && val <= val2;
    }
}

