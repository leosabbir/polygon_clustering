#include "context.h"
#include "constants.h"
#include <iostream>
#include "weightedquickunionuf.h"

Context *(Context::context) = NULL;

Context::Context()
{
    this->polygonComputationUtil = new PolygonComputationUtil();
    this->fileReader = new PolygonsReadWriteUtil();
    //this->fileReader->constructPolygons();
    //this->connectingLines = new QList<CustomeLine>();
    //QList<CustomeLine>* xx = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), 500.0);
    this->fileReader->constructPolygons();
    //this->connectingLines = this->polygonComputationUtil->computeAllOptimumDistances(this->fileReader->constructPolygons(), Constants::INITIAL_THRESHOLD);
    this->convexHullComputationUtil = new ConvexHullComputationUtil();
    this->selectedPolygon = -1;
    this->threshold = Constants::INITIAL_THRESHOLD;
    this->editMode = Constants::DELETE_VERTEX_MODE;
    this->drawConnectingLines = false;
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

PolygonsReadWriteUtil Context::getFileReader() {
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

QList<CustomPoint> Context::computePointsForClustering() {
    return this->polygonComputationUtil->computePointsForClustering();
}

int Context::getSelectedPolygon() {
    return this->selectedPolygon;
}

WeightedQuickUnionUF* Context::getPolygonsUnionFind() {
    return this->polygonsUnionFind;
}

void Context::resetPolygonsUnionFind(int n) {
    delete this->polygonsUnionFind;
    this->polygonsUnionFind = new WeightedQuickUnionUF(n);
}

ConvexHullComputationUtil* Context::getConvexHullComputationalUtil() {
    return this->convexHullComputationUtil;
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
    if (editMode < Constants::NORMAL_MODE || editMode > Constants::CREATE_POLYGONS_MODE) {
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

double Context::getCurrentX() {
    return this->currentX;
}

double Context::getCurrentY() {
    return this->currentY;
}

void Context::setCurrentX(double x) {
    this->currentX = x;
}

void Context::setCurrentY(double y) {
    this->currentY = y;
}
