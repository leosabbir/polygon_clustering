#ifndef INPUTFILEREADER_H
#define INPUTFILEREADER_H

#include <string.h>
#include "custompolygon.h"
#include <QtGui>

class InputFileReader
{
public:
    InputFileReader();
    QList<CustomPolygon> constructPolygons();
    QList<QList<QPoint> > getUiPolygons();
    void updateUiPolygon(int polygonIndex, int vertexIndex, int x, int y);
    void updateSelectedPolygonVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
    bool insertVertex(int selectedPolygon, double x, double y);
    void insertCGALVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
    int hasVertex(int selectedPolygon, double x, double y);


private:
    static const  QString INPUTFILEPATH;
    QFile *file;
    QList<CustomPolygon> *polygonsFromFile;
    QList<QList<QPoint> > *uiPolygons;
};

#endif // INPUTFILEREADER_H
