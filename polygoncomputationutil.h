#ifndef POLYGONCOMPUTATIONUTIL_H
#define POLYGONCOMPUTATIONUTIL_H

#include <QList>
#include <QHash>

#include "pointtocluster.h"
#include "customeline.h"
#include "custompolygon.h"
#include "weightedquickunionuf.h"

class PolygonComputationUtil
{
public:
    PolygonComputationUtil();
    //CustomeLine computeDistance(CustomPolygon p1, CustomPolygon p2);
    //bool doIntersect(CustomPolygon polygon, CustomPolygon line);
    QList<CustomeLine>* computeAllOptimumDistances(QList<CustomPolygon> polygons, double threshold);
    QList<PointToCluster>* computePointsForClustering(bool polygonVertexOnly);
    void clusterVertices();

private:
    QList<PointToCluster> *polygonsPoints;
};

#endif // POLYGONCOMPUTATIONUTIL_H
