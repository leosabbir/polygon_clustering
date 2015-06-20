#ifndef CONTEXT_H
#define CONTEXT_H

#include "inputfilereader.h"
#include "polygoncomputationutil.h"

class Context
{
public:
    static Context getInstance();
    InputFileReader getFileReader();


private:
    Context();
    static Context *context;
    InputFileReader *fileReader;
    PolygonComputationUtil *polygonComputationUtil;
};

#endif // CONTEXT_H
