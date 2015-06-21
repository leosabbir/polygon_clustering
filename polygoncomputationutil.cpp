#include "polygoncomputationutil.h"

PolygonComputationUtil::PolygonComputationUtil()
{

}

QList<CustomeLine>* PolygonComputationUtil::computeAllOptimumDistances(QList<CustomPolygon> polygons, double threshold) {
    QList<CustomeLine> *connectingLines;
    connectingLines = new QList<CustomeLine>();
    for(int i = 0; i < polygons.size()-1; i++) {
        for ( int j = i+1; j < polygons.size(); j++) {
            CustomeLine *connectingLine = polygons.at(i).computeDistance(polygons.at(j));
            //connectingLine = polygons->at(i).computeDistance(polygons->at(j));
            if ( connectingLine->getDistance() <= threshold ) {
                for (int k = 0; k < polygons.size(); k++) {
                    if ( i != k && j != k) {
                        CustomPolygon p;
                        p.push_back(connectingLine->getP());
                        p.push_back(connectingLine->getQ());
                        if (!polygons.at(k).doIntersect(p)) {
                            //polygons->at(i).addConnectingPolygon(j, connectingLine);
                            //polygons->at(j).addConnectingPolygon(i, connectingLine);
                            connectingLines->append(*connectingLine);
                        }
                    }
                }
            }
        }
    }
    return connectingLines;
}

