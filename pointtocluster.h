#ifndef POINTTOCLUSTER_H
#define POINTTOCLUSTER_H

#include "custompoint.h"

class PointToCluster : public CustomPoint
{
public:
    PointToCluster(double x, double y, int clusterIndex, int parentPolygonIndex);

    void setClusterIndex(int clusterIndex);
    int getClusterIndex();
    int getParentPolygonIndex();

private:
    int parentPolygonIndex;
    int clusterIndex;
};

#endif // POINTTOCLUSTER_H
