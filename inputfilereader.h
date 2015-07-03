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
    void updateSelectedPolygonVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
    bool insertVertex(int selectedPolygon, double x, double y);
    void insertCGALVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
    int hasVertex(int selectedPolygon, double x, double y);


private:
    static const  QString INPUTFILEPATH;
    QFile *file;
    QList<CustomPolygon> *polygonsFromFile;
};

#endif // INPUTFILEREADER_H
