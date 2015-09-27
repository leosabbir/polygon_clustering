#include "polygoncomputationutil.h"
#include "context.h"

PolygonComputationUtil::PolygonComputationUtil()
{
    this->polygonsPoints = NULL;
}

QList<CustomeLine>* PolygonComputationUtil::computeAllOptimumDistances(QList<CustomPolygon> polygons, double threshold) {
    QList<CustomeLine> *connectingLines;
    connectingLines = new QList<CustomeLine>();

    Context::getInstance()->resetPolygonsUnionFind(polygons.size()); // polygons.size());
    qDebug() << "No of polygons " << polygons.size();
    for(int i = 0; i < polygons.size()-1; i++) {
        for ( int j = i+1; j < polygons.size(); j++) {
            CustomeLine *connectingLine = polygons.at(i).computeDistance(polygons.at(j));
            if ( connectingLine->getSquaredDistance() <= threshold * threshold ) {
                Context::getInstance()->getPolygonsUnionFind()->ufUnion(i, j);
                bool intersects = false;
                for (int k = 0; k < polygons.size(); k++) {
                    if ( i != k && j != k) {
                        CustomPolygon *p = new CustomPolygon();
                        p->push_back(connectingLine->getP());
                        p->push_back(connectingLine->getQ());
                        if (polygons.at(k).doIntersect(*p)) {
                            intersects = true;
                            break;
                        }
                    }
                }
                if ( !intersects ) {
                    connectingLines->append(*connectingLine);
                }
            }
        }
    }
    return connectingLines;
}

QList<CustomPoint> PolygonComputationUtil::computePointsForClustering() {
    if (this->polygonsPoints == NULL) {
        this->polygonsPoints = new QList<CustomPoint>();
    } else {
        this->polygonsPoints->clear();
    }

    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
    int i = 0;
    for (QList<CustomPolygon>::iterator iter = polygons.begin(); iter != polygons.end(); iter++, i++) {
        double xmax = (*iter).bbox().xmax();
        double xmin = (*iter).bbox().xmin();
        double ymax = (*iter).bbox().ymax();
        double ymin = (*iter).bbox().ymin();
        for(double x = xmin; x <= xmax; x += Constants::DELTA_FOR_POINTS_CLUSTERING) {
            for(double y = ymin; y <= ymax; y += Constants::DELTA_FOR_POINTS_CLUSTERING) {
                CGAL::Bounded_side positionOfPointInPolygon = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(*iter, x, y);
                if(positionOfPointInPolygon != CGAL::ON_UNBOUNDED_SIDE) {
                    this->polygonsPoints->append(*(new CustomPoint(x, y)));
                }
            }
        }

    }
    return *(this->polygonsPoints);
}
