#include "inputfilereader.h"
#include <istream>

const QString InputFileReader::INPUTFILEPATH = ":/resources/input.txt";

InputFileReader::InputFileReader() {
    file = new QFile(this->INPUTFILEPATH);
    this->polygonsFromFile = NULL;
}

QList<CustomPolygon> InputFileReader::constructPolygons() {
    if ( (this->polygonsFromFile) != NULL ) {
        return *(this->polygonsFromFile);
    }
    this->polygonsFromFile = new QList<CustomPolygon>();

    if (file->open(QIODevice::ReadOnly)) {
       QTextStream in(file);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          if (line.startsWith("//") || line.isEmpty()) {
              continue;
          }
          QStringList coordinates = line.split(" ");
          int i = 1;
          double x,y;

          CustomPolygon *cgalPolygon;

          cgalPolygon = new CustomPolygon();
          for ( QStringList::Iterator iter = coordinates.begin(); iter != coordinates.end(); ++iter ) {
              QString strValue = *iter;

              switch (i) {
              case 1:
                  x = strValue.toDouble();
                  i++;
                  break;
              default:
                  i = 1;
                  y = strValue.toDouble();

                  cgalPolygon->push_back(*(new Point(x, y)));
                  break;
              }
          }
          if (cgalPolygon->is_clockwise_oriented()) {
              cgalPolygon->reverse_orientation();
          }
          polygonsFromFile->append(*cgalPolygon);
       }
       file->close();
    } else {
        std::cout << "file could not be read" << std::endl;
    }

    return *(this->polygonsFromFile);
}

void InputFileReader::updateSelectedPolygonVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY) {
    int i = 0;
    for ( QList<CustomPolygon>::iterator polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end() ; polygonIterator++) {
        if ( i != selectedPolygon ) {
            i++;
            continue;
        }
        int j = 0;
        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            if (j == selectedVertexIndex) {
                (*polygonIterator).set(vertexIterator, *(new CustomPoint(newX, newY)));
                //(*polygonIterator).erase(vertexIterator);
                return;
            }
            j++;
        }
        return;
    }
}

void InputFileReader::insertCGALVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY) {
    int i = 0;
    for ( QList<CustomPolygon>::iterator polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end() ; polygonIterator++) {
        if ( i != selectedPolygon ) {
            i++;
            continue;
        }
        int j = 0;
        bool lastVertex = false;
        if (selectedVertexIndex == (*polygonIterator).size()) {
            lastVertex = true;
        }
        qDebug() << "insert at " << selectedVertexIndex;
        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            qDebug() << j;
            if (j == selectedVertexIndex || lastVertex ) {
                qDebug() << "inserting at " << selectedVertexIndex;
                if (lastVertex) {
                    (*polygonIterator).push_back(*(new CustomPoint(newX, newY)));
                } else {
                    (*polygonIterator).insert(vertexIterator, *(new CustomPoint(newX, newY)));
                }
                return;
            }
            j++;
        }
        return;
    }
}

int InputFileReader::hasVertex(int selectedPolygon, double x, double y) {// can anything be done ??
    int index = 0;
    for(QList<CustomPolygon>::iterator polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end(); polygonIterator++) {
        if (index == selectedPolygon) {
            int j = 0;
            for(Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                double vertexX = CGAL::to_double((*vertexIterator).x());
                double vertexY = CGAL::to_double((*vertexIterator).y());

                if ( x >= vertexX - Constants::DELTA && x <= vertexX + Constants::DELTA &&
                     y >= vertexY - Constants::DELTA && y <= vertexY + Constants::DELTA) {
                    return j;
                }
                j++;
            }
            return -1;
        }
        index++;
    }
    return -1;
}

bool InputFileReader::insertVertex(int selectedPolygon, double x, double y) {
    int index = 0;
    for(QList<CustomPolygon>::iterator polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end(); polygonIterator++) {
        if (index == selectedPolygon) {
            int j = 0;
            for(Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                double x1 = CGAL::to_double((*vertexIterator).x());
                double y1 = CGAL::to_double((*vertexIterator).y());

                double x2;
                double y2;
                if (vertexIterator + 1 == (*polygonIterator).vertices_end()) {
                    x2 = CGAL::to_double((*(*polygonIterator).vertices_begin()).x());
                    y2 = CGAL::to_double((*(*polygonIterator).vertices_begin()).y());
                } else {
                    x2 = CGAL::to_double((*(vertexIterator+1)).x());
                    y2 = CGAL::to_double((*(vertexIterator+1)).y());
                }

                //TODO fix for vertical line
                double expectedY;
                if( x2 == x1) {
                    expectedY = y;
                } else {
                    expectedY = (y2-y1)/(x2-x1) * (x-x1) + y1;
                }

                if ( (x2 == x1 && x >= x1 - Constants::DELTA && x <= x1 + Constants::DELTA && Utils::inBetween(y, y1, y2))
                     || (x2 != x1 && y >= expectedY - Constants::DELTA && y <= expectedY + Constants::DELTA && Utils::inBetween(x, x1, x2))) {
                    //qDebug() << "vertexX " << vertexX << "vertexY " << vertexY;
                    //(*polygonIterator).insert(j+1, *(new QPoint(x, y)));
                    bool lastVertex = false;
                    int insertionIndex = j+1;
                    if (insertionIndex == (*polygonIterator).size()) {
                        lastVertex = true;
                    }
                    if (lastVertex) {
                        (*polygonIterator).push_back(*(new CustomPoint(x, y)));
                    } else {
                        (*polygonIterator).insert(vertexIterator+1, *(new CustomPoint(x, y)));
                    }
                    //this->insertCGALVertex(selectedPolygon, j+1, x, y);
                    qDebug() << "Hurray Point found" << expectedY << " " << y;
                    return true;
                }

                j++;
            }
            //return -1;
        }
        index++;
    }
    return false;
}
