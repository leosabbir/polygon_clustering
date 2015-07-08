#ifndef CONTEXT_H
#define CONTEXT_H

#include "inputfilereader.h"
#include "polygoncomputationutil.h"
#include "polygonsintersectionfinder.h"

class Context
{
public:
    static Context* getInstance();
    void reset();
    InputFileReader getFileReader();
    QList<CustomeLine> getConnectingLines();
    void reComputeConnectingLines(int threshold);
    PolygonsIntersectionFinder getCgalUtility();
    int getSelectedPolygon();
    void setSelectedPolygon(int selectedPolygonIndex);
    bool isPolygonSelected();
    int getEditMode();
    void setEditMode(int editMode);
    void setDrawConnectingLines(bool drawConnectingLines);
    bool isDrawConnectingLines();
    double getCurrentX();
    double getCurrentY();
    void setCurrentX(double x);
    void setCurrentY(double y);


private:
    Context();
    static Context *context;
    QList<CustomeLine> *connectingLines;
    InputFileReader *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
    PolygonsIntersectionFinder *cgalUtility;
    int selectedPolygon;
    int threshold;
    int editMode;
    bool drawConnectingLines;
    double currentX;
    double currentY;

};

#endif // CONTEXT_H
