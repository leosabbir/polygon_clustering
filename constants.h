#ifndef CONSTANTS_H
#define CONSTANTS_H


class Constants
{
public:
    Constants();
    static const int INITIAL_THRESHOLD = 100;

    static double WIDTH;
    static double HEIGHT;

    static const int DELTA = 5;

    static const int NORMAL_MODE = 0;
    static const int EDIT_MODE = 1;
    static const int ADD_VERTEX_MODE = 2;
    static const int DELETE_VERTEX_MODE = 3;
};

#endif // CONSTANTS_H
