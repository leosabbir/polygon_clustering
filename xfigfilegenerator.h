#ifndef XFIGFILEGENERATOR_H
#define XFIGFILEGENERATOR_H

#include "custompolygon.h"

class XfigFileGenerator
{
public:
    XfigFileGenerator();
    void initialize(QString filePath);
    void drawPolygons(QList<CustomPolygon> polygons);
    void drawLine(double x1, double y1, double x2, double y2);

private:
    QString *currentFile;
};

#endif // XFIGFILEGENERATOR_H
