#include "xfigfilegenerator.h"

XfigFileGenerator::XfigFileGenerator(QString filePath){
    this->currentFile = new QString();
    this->magnification = 10;
    this->initialize(filePath);
}

void XfigFileGenerator::initialize(QString filePath) {
    QFile *outputFile = new QFile(filePath);

    this->currentFile->clear();
    this->currentFile->append(filePath);

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Text) ) {
        outputFile->resize(0);
        QTextStream stream( outputFile );

        qDebug() << "Saving the XFig file: " << filePath;
        stream << "#FIG 3.2  Produced by xfig version 3.2.5c" << endl;
        stream << "Landscape" << endl;
        stream << "Center" << endl;
        stream << "Metric" << endl;
        stream << "A4" << endl;
        stream << "100.00" << endl;
        stream << "Single" << endl;
        stream << "-2" << endl;
        stream << "1200 2" << endl;
        //stream << x << " " << y << " ";
        //stream << endl;
        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << filePath;
    }
}

void XfigFileGenerator::drawPolygons(QList<CustomPolygon> polygons) {
    QFile *outputFile = new QFile(*(this->currentFile));

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QList<CustomPolygon>::iterator polygonIterator;
        QTextStream stream( outputFile );

        for ( polygonIterator = polygons.begin(); polygonIterator != polygons.end() ; polygonIterator++) {
            stream << "2 3 0 1 0 7 50 -1 -1 0.000 0 0 -1 0 0 " << (*polygonIterator).size() + 1 << endl;
            for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                double x = CGAL::to_double((*vertexIterator).x()) * this->magnification;
                double y = CGAL::to_double((*vertexIterator).y()) * this->magnification;

                stream << x << " " << 6000 - y << " ";
            }
            //Append initial point to complete cycle
            Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin();
            double x = CGAL::to_double((*vertexIterator).x()) * this->magnification;
            double y = CGAL::to_double((*vertexIterator).y()) * this->magnification;
            stream << x << " " << 6000 - y;

            stream << endl;
        }
        //stream << x << " " << y << " ";
        //stream << endl;
        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << *(this->currentFile);
    }
}

void XfigFileGenerator::drawPolygon(CustomPolygon polygon) {
    QFile *outputFile = new QFile(*(this->currentFile));

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QList<CustomPolygon>::iterator polygonIterator;
        QTextStream stream( outputFile );

        stream << "2 3 0 1 0 7 50 -1 -1 0.000 0 0 -1 0 0 " << polygon.size() + 1 << endl;
        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            double x = CGAL::to_double((*vertexIterator).x()) * this->magnification;
            double y = CGAL::to_double((*vertexIterator).y()) * this->magnification;

            stream << x << " " << 6000 - y << " ";
        }

        //Append initial point to complete cycle
        Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin();
        double x = CGAL::to_double((*vertexIterator).x()) * this->magnification;
        double y = CGAL::to_double((*vertexIterator).y()) * this->magnification;
        stream << x << " " << 6000 - y;

        stream << endl;

        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << *(this->currentFile);
    }
}

void XfigFileGenerator::drawLines(QList<CustomPoint> vertices) {
    QFile *outputFile = new QFile(*(this->currentFile));

    if ( outputFile->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text) ) {
        QTextStream stream( outputFile );

        for ( QList<CustomPoint>::iterator vertexIterator = vertices.begin(); vertexIterator != vertices.end(); vertexIterator++) {
            stream << "2 1 0 1 0 7 50 -1 -1 0.000 0 0 -1 0 0 2" << endl;
            //stream << Utils::transform(CGAL::to_double((*vertexIterator).x()), Constants::WIDTH) << Utils::transform(CGAL::to_double((*vertexIterator).y()), Constants::HEIGHT);
            stream << (int) CGAL::to_double((*vertexIterator).x())  * this->magnification << " " << 6000 - (int) CGAL::to_double((*vertexIterator).y()) * this->magnification << " ";
            vertexIterator++;
            //stream << Utils::transform(CGAL::to_double((*vertexIterator).x()), Constants::WIDTH) << Utils::transform(CGAL::to_double((*vertexIterator).y()), Constants::HEIGHT);
            stream << (int) CGAL::to_double((*vertexIterator).x()) * this->magnification << " " << 6000 - (int) CGAL::to_double((*vertexIterator).y()) * this->magnification;
            stream << endl;
        }

        stream.flush();
        outputFile->close();
    } else {
        qDebug() << "Error Opening the XFig file: " << *(this->currentFile);
    }
}
