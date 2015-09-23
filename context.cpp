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
    this->polygonsPoints = NULL;
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

//MOVE computation to different place
QList<CustomPoint> Context::computePointsForClustering() {
    if (this->polygonsPoints == NULL) {
        this->polygonsPoints = new QList<CustomPoint>();
    } else {
        this->polygonsPoints->clear();
    }

    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();

    int i = 0;
    for (QList<CustomPolygon>::iterator iter = polygons.begin(); iter != polygons.end(); iter++, i++) {
        double xmax = (*iter).bbox().xmax();
        double xmin = (*iter).bbox().xmin();
        double ymax = (*iter).bbox().ymax();
        double ymin = (*iter).bbox().ymin();
        for(double x = xmin; x <= xmax; x += Constants::DELTA_FOR_POINTS_CLUSTERING) {
            for(double y = ymin; y <= ymax; y += Constants::DELTA_FOR_POINTS_CLUSTERING) {
                CGAL::Bounded_side positionOfPointInPolygon = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(*iter, x, y);
                if(positionOfPointInPolygon != CGAL::ON_UNBOUNDED_SIDE) {
                    this->polygonsPoints->append(*(new CustomPoint(x, y)));
                }
            }
        }

    }
    return *(this->polygonsPoints);
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
