#include "context.h"
#include <iostream>

Context *(Context::context) = NULL;

Context::Context()
{
    this->polygonComputationUtil = new PolygonComputationUtil();
    this->fileReader = new InputFileReader();
    //this->fileReader->constructPolygons();
    //this->connectingLines = new QList<CustomeLine>();
    //QList<CustomeLine>* xx = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), 500.0);
    this->connectingLines = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), 1000.0);
}

Context* Context::getInstance() {
    if (Context::context == NULL) {
        Context::context = new Context();
    }
    return Context::context;
}

InputFileReader Context::getFileReader() {
    return *(this->fileReader);
}

QList<CustomeLine> Context::getConnectingLines() {
    return *(this->connectingLines);
}

void Context::reComputeConnectingLines(int threshold) {
    std::cout << "recomputing" << std::endl;
    this->connectingLines = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), threshold^2);
}

