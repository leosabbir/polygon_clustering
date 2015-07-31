#ifndef INPUTFILEREADER_H
#define INPUTFILEREADER_H

#include <string.h>
#include "custompolygon.h"
#include <QtGui>

class InputFileReader {
    public:
        InputFileReader();
        QList<CustomPolygon> constructPolygons();
        void insertPolygon(CustomPolygon polygon);
        void updateSelectedPolygonVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
        void movePolygon(int selectedPolygon, double deltaX, double deltaY);
        bool insertVertex(int selectedPolygon, double x, double y);
        void insertCGALVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY);
        bool removeVertex(int selectedPolygon, int selectedVertexIndex, double x, double y);
        int hasVertex(int selectedPolygon, double x, double y);


    private:
        static const  QString INPUTFILEPATH;
        QFile *file;
        QList<CustomPolygon> *polygonsFromFile;
};

#endif // INPUTFILEREADER_H
