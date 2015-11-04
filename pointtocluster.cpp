#include "pointtocluster.h"

PointToCluster::PointToCluster(double x, double y, int clusterIndex, int parentPolygonIndex):CustomPoint(x, y) {
    this->clusterIndex = clusterIndex;
    this->parentPolygonIndex = parentPolygonIndex;
}

void PointToCluster::setClusterIndex(int clusterIndex) {
    this->clusterIndex = clusterIndex;
}

int PointToCluster::getClusterIndex() {
    return this->clusterIndex;
}

int PointToCluster::getParentPolygonIndex() {
    return this->clusterIndex;
}
