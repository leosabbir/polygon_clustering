#ifndef CONTEXT_H
#define CONTEXT_H

#include "inputfilereader.h"
#include "polygoncomputationutil.h"

class Context
{
public:
    static Context* getInstance();
    InputFileReader getFileReader();
    QList<CustomeLine> getConnectingLines();
    void reComputeConnectingLines(int threshold);


private:
    Context();
    static Context *context;
    QList<CustomeLine> *connectingLines;
    InputFileReader *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
};

#endif // CONTEXT_H
