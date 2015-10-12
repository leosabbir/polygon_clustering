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

QList<CustomPoint>* PolygonComputationUtil::computePointsForClustering(bool polygonVertexOnly) {
    if (this->polygonsPoints == NULL) {
        this->polygonsPoints = new QList<CustomPoint>();
    } else {
        this->polygonsPoints->clear();
    }

    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
    int i = 0;
    for (QList<CustomPolygon>::iterator polygonIterator = polygons.begin(); polygonIterator != polygons.end(); polygonIterator++, i++) {
        if (!polygonVertexOnly) {
            double xmax = (*polygonIterator).bbox().xmax();
            double xmin = (*polygonIterator).bbox().xmin();
            double ymax = (*polygonIterator).bbox().ymax();
            double ymin = (*polygonIterator).bbox().ymin();
            for(double x = xmin; x <= xmax; x += Constants::DELTA_FOR_POINTS_CLUSTERING) {
                for(double y = ymin; y <= ymax; y += Constants::DELTA_FOR_POINTS_CLUSTERING) {
                    CGAL::Bounded_side positionOfPointInPolygon = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(*polygonIterator, x, y);
                    if(positionOfPointInPolygon == CGAL::ON_BOUNDED_SIDE) {
                        this->polygonsPoints->append(*(new CustomPoint(x, y)));
                    }
                }
            }
        }

        //ADD VERTICES on the Boundary
        Vertex_iterator next;
        for (Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            next = vertexIterator + 1;
            if (next == (*polygonIterator).vertices_end()) {
                next = (*polygonIterator).vertices_begin();
            }
            double x1 = CGAL::to_double((*vertexIterator).x());
            double y1 = CGAL::to_double((*vertexIterator).y());
            double x2 = CGAL::to_double((*next).x());
            double y2 = CGAL::to_double((*next).y());

            this->polygonsPoints->append(*(new CustomPoint(x1, y1)));
            if (!polygonVertexOnly) {
                int dx = 1;
                int dy = 1;
                if (y2 < y1) {
                    dy = -1;
                }
                if (x2 < x1) {
                    dx = -1;
                }

                if (y1 == y2) {
                    double x = x1 + Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dx;
                    while ((dx == 1 && x < x2) || (dx == -1 && x > x2)) {
                        this->polygonsPoints->append(*(new CustomPoint(x, y1)));
                        x += Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dx;
                    }
                } else if ( x1 == x2) {
                    double y = y1 + Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dy;
                    while ((dy == 1 && y < y2) || (dy == -1 && y > y2)) {
                        this->polygonsPoints->append(*(new CustomPoint(x1, y)));
                        y += Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dy;
                    }
                } else {
                    double m = (y2 - y1) / (x2 - x1);
                    double c = y1 - m * x1;

                    if ((m < 0 && m > -.5) || (m > 0 && m < .5)) {
                        double x = x1 + Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dx;
                        double y = m * x + c;
                        while((dy == 1 && y < y2) || (dy == -1 && y > y2)) {
                            this->polygonsPoints->append(*(new CustomPoint(x, y)));
                            x += Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dx;
                            y = m * x + c;
                        }
                    } else {
                        double y = y1 + Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY *dy;
                        double x = (y - c) / m;
                        while ((dx == 1 && x < x2) || (dx == -1 && x > x2)) {
                            this->polygonsPoints->append(*(new CustomPoint(x, y)));
                            y += Constants::DELTA_FOR_POINTS_CLUSTERING_BOUNDARY * dy;
                            x = (y - c) / m;
                        }
                    }

                }
            }
            this->polygonsPoints->append(*(new CustomPoint(x2, y2)));
        }
        //END ADD VERTICES on the Boundary

    }
    return (this->polygonsPoints);
}
