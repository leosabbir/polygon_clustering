#ifndef XFIGFILEGENERATOR_H
#define XFIGFILEGENERATOR_H

#include "custompolygon.h"
#include <QList>
#include <QFile>

class XfigFileGenerator
{
public:
    XfigFileGenerator(QString filePath);
    void initialize(QString filePath);
    void drawPolygons(QList<CustomPolygon> polygons);
    void drawPolygon(CustomPolygon polygon);
    void drawLines(QList<CustomPoint> vertices, bool drawDashed);
    void drawLine(double x1, double y1, double x2, double y2, bool drawDashed);

private:
    QString *currentFile;
    int magnification;
};

#endif // XFIGFILEGENERATOR_H
