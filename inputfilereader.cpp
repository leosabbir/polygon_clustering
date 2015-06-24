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
    //file->setFileName(this->INPUTFILEPATH);
}

QList<CustomPolygon> InputFileReader::constructPolygons() {
    QList<CustomPolygon> *polygons;
    polygons = new QList<CustomPolygon>();
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
          this->uiPolygons << *polygon;
          if (cgalPolygon->is_clockwise_oriented()) {
              cgalPolygon->reverse_orientation();
          }
          polygons->append(*cgalPolygon);
          //std::cout << std::endl;
       }
       file->close();
    } else {
        std::cout << "file could not be read" << std::endl;
    }

    return *polygons;
}

QList<QList<QPoint> > InputFileReader::getUiPolygons() {
    return this->uiPolygons;
}
