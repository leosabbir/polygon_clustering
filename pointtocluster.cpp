#include "pointtocluster.h"

PointToCluster::PointToCluster(double x, double y, int clusterIndex, int parentPolygonIndex):CustomPoint(x, y) {
    this->clusterIndex = clusterIndex;
    this->parentPolygonIndex = parentPolygonIndex;
}
