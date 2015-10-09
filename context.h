#ifndef CONTEXT_H
#define CONTEXT_H

#include "polygonsreadwriteutil.h"
#include "polygoncomputationutil.h"
#include "polygonsintersectionfinder.h"
#include "weightedquickunionuf.h"
#include "convexhullcomputationutil.h"

class Context
{
public:
    static Context* getInstance();
    void reset();
    PolygonsReadWriteUtil getFileReader();
    QList<CustomeLine> getConnectingLines();
    void reComputeConnectingLines(int threshold);
    QList<CustomPoint> computePointsForClustering();
    PolygonsIntersectionFinder getCgalUtility();
    int getSelectedPolygon();
    void setSelectedPolygon(int selectedPolygonIndex);
    bool isPolygonSelected();
    int getEditMode();
    void setEditMode(int editMode);
    void setDrawConnectingLines(bool drawConnectingLines);
    bool isDrawConnectingLines();
    WeightedQuickUnionUF* getPolygonsUnionFind();
    void resetPolygonsUnionFind(int n);
    ConvexHullComputationUtil* getConvexHullComputationalUtil();
    double getCurrentX();
    double getCurrentY();
    void setCurrentX(double x);
    void setCurrentY(double y);
    bool isBorderEnabled();
    bool isVerticesEnabled();
    void setBorderEnabled(bool borderEnabled);
    void setVerticesEnabled(bool verticesEnabled);


private:
    Context();
    static Context *context;
    QList<CustomeLine> *connectingLines;
    PolygonsReadWriteUtil *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
    PolygonsIntersectionFinder *cgalUtility;
    WeightedQuickUnionUF *polygonsUnionFind;
    ConvexHullComputationUtil *convexHullComputationUtil;
    int selectedPolygon;
    int threshold;
    int editMode;
    bool drawConnectingLines;
    double currentX;
    double currentY;
    bool borderEnabled;
    bool verticesEnabled;
    bool polygonVertexOnly;

};

#endif // CONTEXT_H
