#include "context.h"
#include "constants.h"
#include <iostream>

Context *(Context::context) = NULL;

Context::Context()
{
    this->polygonComputationUtil = new PolygonComputationUtil();
    this->fileReader = new InputFileReader();
    //this->fileReader->constructPolygons();
    //this->connectingLines = new QList<CustomeLine>();
    //QList<CustomeLine>* xx = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), 500.0);
    this->connectingLines = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), Constants::INITIAL_THRESHOLD);
    this->selectedPolygon = -1;
    this->threshold = Constants::INITIAL_THRESHOLD;
    this->editMode = Constants::DELETE_VERTEX_MODE;
    this->drawConnectingLines = true;
}

void Context::reset() {
    this->reComputeConnectingLines(this->threshold);
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

PolygonsIntersectionFinder Context::getCgalUtility() {
    return *(this->cgalUtility);
}

void Context::reComputeConnectingLines(int threshold) {
    std::cout << "recomputing" << std::endl;
    this->threshold = threshold;
    this->connectingLines = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), threshold);
}

int Context::getSelectedPolygon() {
    return this->selectedPolygon;
}

void Context::setSelectedPolygon(int selectedPolygonIndex) {
    this->selectedPolygon = selectedPolygonIndex;
}

bool Context::isPolygonSelected() {
    return this->selectedPolygon > -1;
}

int Context::getEditMode() {
    return this->editMode;
}

void Context::setEditMode(int editMode) {
    if (editMode < Constants::NORMAL_MODE || editMode > Constants::DELETE_VERTEX_MODE) {
        throw std::invalid_argument("Invalid Edit Mode");
    }
    this->editMode = editMode;
}

void Context::setDrawConnectingLines(bool drawConnectingLines) {
    this->drawConnectingLines = drawConnectingLines;
}

bool Context::isDrawConnectingLines() {
    return this->drawConnectingLines;
}
