#include "utils.h"

Utils::Utils()
{

}

double Utils::transform(double coord, double total) {
    double transformed = (coord * 1.0 - total)/total;
    transformed = coord * 1.0 / total;
    return transformed * 2 - 1;
}

