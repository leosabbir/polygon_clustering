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


private:
    static const  QString INPUTFILEPATH;
    QFile *file;
    QList<QList<QPoint> > uiPolygons;
};

#endif // INPUTFILEREADER_H
