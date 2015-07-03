#ifndef UTILS_H
#define UTILS_H


class Utils
{
public:
    Utils();

    static double transform(double coord, double total);
    static bool inBetween(double val, double val1, double val2);
};

#endif // UTILS_H
