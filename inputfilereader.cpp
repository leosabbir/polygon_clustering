#include "inputfilereader.h"
#include <istream>

const QString InputFileReader::INPUTFILEPATH = ":/resources/input.txt";

InputFileReader::InputFileReader()
{
    //QDir::setCurrent("/home/laxmi/Documents/sabbirThesis/cluster_obstacles/");
    //QDir::setCurrent(".");
    //QDir::setCurrent(QCoreApplication::applicationDirPath());
    //std::cout << QDir::currentPath().toUtf8().constData() << std::endl;
    file = new QFile(this->INPUTFILEPATH);
    this->polygonsFromFile = NULL;
    //file->setFileName(this->INPUTFILEPATH);
}

QList<CustomPolygon> InputFileReader::constructPolygons() {
    if ( (this->polygonsFromFile) != NULL ) {
        return *(this->polygonsFromFile);
    }
    this->polygonsFromFile = new QList<CustomPolygon>();
    this->uiPolygons = new QList<QList<QPoint> >;
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
          QList<QPoint> *polygon;
          CustomPolygon *cgalPolygon;
          polygon = new QList<QPoint>();
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
                  *polygon << QPoint(x, y);
                  cgalPolygon->push_back(*(new Point(x, y)));
                  break;
              }
              //std::cout << " " << strValue.toDouble(); //<< strValue.toUtf8().constData();
          }
          *(this->uiPolygons) << *polygon;
          if (cgalPolygon->is_clockwise_oriented()) {
              //cgalPolygon->reverse_orientation();
          }
          polygonsFromFile->append(*cgalPolygon);
          //std::cout << std::endl;
       }
       file->close();
    } else {
        std::cout << "file could not be read" << std::endl;
    }

    return *(this->polygonsFromFile);
}

QList<QList<QPoint> > InputFileReader::getUiPolygons() {
    return *(this->uiPolygons);
}

void InputFileReader::updateUiPolygon(int polygonIndex, int vertexIndex, int x, int y) {
    int i = 0;
    for(QList<QList<QPoint> >::iterator polygonIterator = this->uiPolygons->begin(); polygonIterator != this->uiPolygons->end(); polygonIterator++) {
        if (i == polygonIndex) {
            int j = 0;
            for(QList<QPoint>::iterator vertexIterator = (*polygonIterator).begin(); vertexIterator != (*polygonIterator).end(); vertexIterator++) {
                if (j == vertexIndex) {
                    (*vertexIterator).setX(x);
                    (*vertexIterator).setY(y);
                    break;
                }
                j++;
            }
            break;
        }
        i++;
    }
}

void InputFileReader::updateSelectedPolygonVertex(int selectedPolygon, int selectedVertexIndex, double newX, double newY) {
    int i = 0;
    for ( QList<CustomPolygon>::iterator polygonIterator = this->polygonsFromFile->begin(); polygonIterator != this->polygonsFromFile->end() ; polygonIterator++) {
        if ( i != selectedPolygon ) {
            i++;
            continue;
        }
        //qDebug() << "match found";
        int j = 0;
        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            //qDebug() << selectedVertexIndex;
            if (j == selectedVertexIndex) {
                //qDebug() << (*polygonIterator).size();
                (*polygonIterator).set(vertexIterator, *(new CustomPoint(newX, newY)));
                //(*polygonIterator).erase(vertexIterator);
                //(*polygonIterator).insert(vertexIterator, *(new CustomPoint(newX, newY)));
                //(*polygonIterator).clear();
                //qDebug() << (*polygonIterator).size();
                //qDebug() << "inserted";
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
        //qDebug() << "match found";
        int j = 0;
        if (selectedVertexIndex == (*polygonIterator).size()) {
            selectedVertexIndex--;
        }
        qDebug() << "insert at " << selectedVertexIndex;
        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            //qDebug() << selectedVertexIndex;
            if (j == selectedVertexIndex) {
                //qDebug() << (*polygonIterator).size();
                //(*polygonIterator).set(vertexIterator, *(new CustomPoint(newX, newY)));
                //(*polygonIterator).erase(vertexIterator);
                qDebug() << "inserting at " << selectedVertexIndex;
                (*polygonIterator).insert(vertexIterator, *(new CustomPoint(newX, newY)));
                //(*polygonIterator).clear();
                //qDebug() << (*polygonIterator).size();
                //qDebug() << "inserted";
                return;
            }
            j++;
        }
        return;
    }
}

int InputFileReader::hasVertex(int selectedPolygon, double x, double y) {
    int index = 0;
    for(QList<QList<QPoint> >::iterator polygonIterator = this->uiPolygons->begin(); polygonIterator != this->uiPolygons->end(); polygonIterator++) {
        if (index == selectedPolygon) {
            int j = 0;
            for(QList<QPoint>::iterator vertexIterator = (*polygonIterator).begin(); vertexIterator != (*polygonIterator).end(); vertexIterator++) {
                double vertexX = (*vertexIterator).x();
                double vertexY = (*vertexIterator).y();

                if ( x >= vertexX - Constants::DELTA && x <= vertexX + Constants::DELTA &&
                     y >= vertexY - Constants::DELTA && y <= vertexY + Constants::DELTA) {
                    //qDebug() << "vertexX " << vertexX << "vertexY " << vertexY;
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
    for(QList<QList<QPoint> >::iterator polygonIterator = this->uiPolygons->begin(); polygonIterator != this->uiPolygons->end(); polygonIterator++) {
        if (index == selectedPolygon) {
            int j = 0;
            for(QList<QPoint>::iterator vertexIterator = (*polygonIterator).begin(); vertexIterator != (*polygonIterator).end(); vertexIterator++) {
                double x1 = (*vertexIterator).x();
                double y1 = (*vertexIterator).y();

                double x2;
                double y2;
                if (vertexIterator + 1 == (*polygonIterator).end()) {
                    x2 = (*(*polygonIterator).begin()).x();
                    y2 = (*(*polygonIterator).begin()).y();
                } else {
                    x2 = (*(vertexIterator+1)).x();
                    y2 = (*(vertexIterator+1)).y();
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
                    (*polygonIterator).insert(j+1, *(new QPoint(x, y)));
                    this->insertCGALVertex(selectedPolygon, j+1, x, y);
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
