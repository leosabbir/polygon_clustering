#include "convexhullcomputationutil.h"
#include "utils.h"
#include "constants.h"
#include "context.h"

ConvexHullComputationUtil::ConvexHullComputationUtil() {
}

void ConvexHullComputationUtil::compute(QList<CustomPolygon> polygons, std::vector<std::vector<PointForConvexHull> > &results) {
    if (polygons.size() == 0) {
        return;
    }
    unordered_map<int, list<int> > components = Context::getInstance()->getPolygonsUnionFind()->getComponents();
    for (auto it = components.begin(); it != components.end(); ++it) {
        //qDebug() << "size : " << (it->second).size() << " ";
        //cout << "component: ";
        std::vector<PointForConvexHull> inputPoints;
        std::vector<PointForConvexHull> *result = new std::vector<PointForConvexHull>();
        for (list<int>::iterator it2 = (it->second).begin(); it2 != (it->second).end(); ++it2) {
            int polygonIndex = *it2;
            //qDebug() << "polygonIndex: " << *it2 << " " << polygonIndex;
            CustomPolygon polygon = polygons.at(polygonIndex);
            for ( Vertex_iterator vertexIterator = polygon.vertices_begin(); vertexIterator != polygon.vertices_end(); vertexIterator++) {
                double x = Utils::transform(CGAL::to_double((*vertexIterator).x()), Constants::WIDTH);
                double y = Utils::transform(CGAL::to_double((*vertexIterator).y()), Constants::HEIGHT);

                inputPoints.push_back(PointForConvexHull(x, y));
            }
        }
        CGAL::convex_hull_2(inputPoints.begin(), inputPoints.end(), std::back_inserter(*result));
        //qDebug() << "Size " << result->size();
        results.push_back(*result);
    }
}
