#ifndef CONTEXT_H
#define CONTEXT_H

#include "inputfilereader.h"
#include "polygoncomputationutil.h"
#include "polygonsintersectionfinder.h"

class Context
{
public:
    static Context* getInstance();
    InputFileReader getFileReader();
    QList<CustomeLine> getConnectingLines();
    void reComputeConnectingLines(int threshold);
    PolygonsIntersectionFinder getCgalUtility();


private:
    Context();
    static Context *context;
    QList<CustomeLine> *connectingLines;
    InputFileReader *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
    PolygonsIntersectionFinder *cgalUtility;

};

#endif // CONTEXT_H
