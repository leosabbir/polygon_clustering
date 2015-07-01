#ifndef CONTEXT_H
#define CONTEXT_H

#include "inputfilereader.h"
#include "polygoncomputationutil.h"
#include "polygonsintersectionfinder.h"
#include "enums.h"

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
    //EDIT_MODE getEditMode();
    //void setEditMode(EDIT_MODE editMode);


private:
    Context();
    static Context *context;
    QList<CustomeLine> *connectingLines;
    InputFileReader *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
    PolygonsIntersectionFinder *cgalUtility;
    int selectedPolygon;
    int threshold;
    //EDIT_MODE editMode;

};

#endif // CONTEXT_H
