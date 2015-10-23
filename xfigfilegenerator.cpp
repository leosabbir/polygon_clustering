#include "xfigfilegenerator.h"

XfigFileGenerator::XfigFileGenerator(){
    this->currentFile = new QString();
}

void XfigFileGenerator::initialize(QString filePath) {
    QFile *outputFile = new QFile(filePath);

    this->currentFile->clear();
    this->currentFile->append(fileName);

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QTextStream stream( outputFile );

        qDebug() << "Saving the XFig file: " << fileName;
        stream << "#FIG 3.2  Produced by xfig version 3.2.5c";
        stream << "Landscape";
        stream << "Center";
        stream << "Metric";
        stream << "A4";
        stream << "100.00";
        stream << "Single";
        stream << "-2";
        stream << "1200 2";
        //stream << x << " " << y << " ";
        //stream << endl;
        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << fileName;
    }
}

void XfigFileGenerator::drawPolygons(QList<CustomPolygon> polygons) {
    QFile *outputFile = new QFile(*(this->currentFile));

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QList<CustomPolygon>::iterator polygonIterator;
        QTextStream stream( outputFile );

        for ( polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end() ; polygonIterator++) {
            stream << "2 3 0 1 0 7 50 -1 -1 0.000 0 0 -1 0 0 ";
            stream << polygons.size();
            for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                double x = CGAL::to_double((*vertexIterator).x());
                double y = CGAL::to_double((*vertexIterator).y());

                stream << x << " " << y << " ";
            }
            stream << endl;
        }
        //stream << x << " " << y << " ";
        //stream << endl;
        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << fileName;
    }
}

void XfigFileGenerator::drawLine(double x1, double y1, double x2, double y2) {
    QFile *outputFile = new QFile(*(this->currentFile));

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QTextStream stream( outputFile );

        stream << "2 1 0 1 0 7 50 -1 -1 0.000 0 0 -1 0 0 2";
        stream << x1 << " " << y1 << " " << x2 << " " << y2;
        stream << endl;

        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << fileName;
    }
}
