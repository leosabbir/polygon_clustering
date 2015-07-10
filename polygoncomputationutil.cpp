#include "polygoncomputationutil.h"
#include "context.h"

PolygonComputationUtil::PolygonComputationUtil()
{

}

QList<CustomeLine>* PolygonComputationUtil::computeAllOptimumDistances(QList<CustomPolygon> polygons, double threshold) {
    QList<CustomeLine> *connectingLines;
    connectingLines = new QList<CustomeLine>();

    //Context::getInstance()->resetPolygonsUnionFind(polygons.size()); // polygons.size());
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
