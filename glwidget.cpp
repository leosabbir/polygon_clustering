#include "glwidget.h"
#include <iostream>
#include <GL/glut.h>
#include <QList>
#include <QPoint>
#include <dummydata.h>
#include "polygonsreadwriteutil.h"
#include "context.h"
#include "customeline.h"
#include "vdutil.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    Constants::WIDTH = this->size().width();
    Constants::HEIGHT = this->size().height();
    this->newPolygon = NULL;
    //this->selectedPolygon = NULL;
    //setMouseTracking(true); // if this is set, then mouse movement will be tracked even if not pressed
}

//GLWidget::~GLWidget() {

//}

void GLWidget::initiallizeGL(){
    glClearColor(0.2, 0.2, 0.2, 1);

}

void GLWidget::paintGL() {
    glClearColor(0.82, 0.82, 0.82, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    double width = Constants::WIDTH = size().width();
    double height = Constants::HEIGHT = size().height();

    //glutWireTeapot(0.6);
    glColor3f(1, 0, 0);

    /****/
    if (Context::getInstance()->isBorderEnabled()) {
        int i = 0;
        QList<CustomPolygon>::iterator polygonIterator;
        QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
        for ( polygonIterator = polygons.begin(); polygonIterator != polygons.end() ; polygonIterator++) {
            glLineWidth(2.0);
            glBegin(GL_LINE_LOOP);
            bool isSelectedPolygon = i++ == Context::getInstance()->getSelectedPolygon();
            if (isSelectedPolygon) {
                glColor3f(0, 0, 1);
            } else {
                //glColor3f(0.58, 0.157, 0.157);
                glColor3f(0, 0, 0);
            }

            for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
            }
            glEnd();
            if (isSelectedPolygon) {
                glColor3f(0, 0, 0);
                glEnable(GL_POINT_SMOOTH);
                glPointSize(3.0);
                glBegin(GL_POINTS);
                for (Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
                    //QPoint vertex = *vertexIterator;
                    glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
                }
                glEnd();
            }
        }
    }
    /****/

    /*** Draw vertices of new polygon ****/
    if (Context::getInstance()->getEditMode() == Constants::CREATE_POLYGONS_MODE && this->newPolygon != NULL) {
        glColor3f(0, 0, 0);
        glEnable(GL_POINT_SMOOTH);
        glPointSize(1.0);
        glBegin(GL_POINTS);
        for ( Vertex_iterator vertexIterator = this->newPolygon->vertices_begin(); vertexIterator != this->newPolygon->vertices_end(); vertexIterator++) {
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
        }
        glEnd();
    }
    /*******/

    QList<PointToCluster>* polygonsPoints = Context::getInstance()->computePointsForClustering();
    /***Draw Polygon Inner Vertices****/
    if (Context::getInstance()->isVerticesEnabled()) {

        glEnable(GL_POINT_SMOOTH);
        glPointSize(3.0);
        glBegin(GL_POINTS);


        QList<PointToCluster>::iterator pointsIterator;
        for ( pointsIterator = polygonsPoints->begin(); pointsIterator != polygonsPoints->end(); pointsIterator++) {
            int index = (*pointsIterator).getClusterIndex();
            switch (index) {
                case 0:
                    glColor3f(0, 0, 0);
                    break;
                case 1:
                    glColor3f(0, 1, 0);
                    break;
                case 2:
                    glColor3f(0, 0, 1);
                    break;
                case 3:
                    glColor3f(1, 0, 0);
                    break;
                case 4:
                    glColor3f(0, 1, 1);
                    break;
                case 5:
                    glColor3f(1, 0, 1);
                    break;
                default:
                    glColor3f(1, 1, 0);
                    break;
            }

            glVertex2d(transformX(CGAL::to_double((*pointsIterator).x()), width), transformY(CGAL::to_double((*pointsIterator).y()), height));
            //qDebug() << (*pointsIterator).getClusterIndex();
        }
        glEnd();
    }
    /*******/

    /***Draw Voronoi Diagram*****/
    if (Context::getInstance()->isVerticesEnabled() && Context::getInstance()->isDrawVoronoi()) {
        VDUtil vdUtil;
        vdUtil.construct(*polygonsPoints, !Context::getInstance()->isDrawOnlyNonIntersectingVoronoiEdges());
        QList<CustomPoint> voronoiLineSegments = vdUtil.getVoronoiLineSegments();

        glLineWidth(2.0);
        glBegin(GL_LINES);
        //glColor3f(1, 1, 0);
        glColor3f(0.58, 0.157, 0.157);
        for ( QList<CustomPoint>::iterator vertexIterator = voronoiLineSegments.begin(); vertexIterator != voronoiLineSegments.end(); vertexIterator++) {
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
            //qDebug() << "Source: " << CGAL::to_double((*vertexIterator).x()) << ", " << CGAL::to_double((*vertexIterator).y());
            vertexIterator++;
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
            //qDebug() << "Target: " << CGAL::to_double((*vertexIterator).x()) << ", " << CGAL::to_double((*vertexIterator).y());
        }
        glEnd();

        glPushAttrib(GL_ENABLE_BIT);
        glLineWidth(2.0);
        glLineStipple(2, 0xAAAA);
        glEnable(GL_LINE_STIPPLE);
        glBegin(GL_LINES);
        //glColor3f(1, 1, 0);
        glColor3f(0.58, 0.157, 0.157);
        QList<CustomPoint> intersectingVoronoiLineSegments = vdUtil.getIntersectingVoronoiLineSegments();
        for ( QList<CustomPoint>::iterator vertexIterator = intersectingVoronoiLineSegments.begin(); vertexIterator != intersectingVoronoiLineSegments.end(); vertexIterator++) {
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
            //qDebug() << "Source: " << CGAL::to_double((*vertexIterator).x()) << ", " << CGAL::to_double((*vertexIterator).y());
            vertexIterator++;
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
            //qDebug() << "Target: " << CGAL::to_double((*vertexIterator).x()) << ", " << CGAL::to_double((*vertexIterator).y());
        }
        glEnd();
        glPopAttrib();
    }
    /***End Draw Voronoi Diagram*****/

    /***Draw Connecting Lines***/
    if (Context::getInstance()->isDrawConnectingLines()) {
        std::vector<std::vector<PointForConvexHull> > results;
        Context::getInstance()->getConvexHullComputationalUtil()->compute(Context::getInstance()->getFileReader().constructPolygons(), results);
        //glColor3f(0.051, 0.369, 0.031);
        glColor3f(0.58, 0.157, 0.157);
        glLineWidth(2.0);
        QList<CustomeLine>::iterator linesIterator;
        QList<CustomeLine> connectingLines = Context::getInstance()->getConnectingLines();
        //std::cout << connectingLines.size() << " lines in the list" << std::endl;
        for (linesIterator = connectingLines.begin(); linesIterator != connectingLines.end(); linesIterator++) {
            glBegin(GL_LINE_LOOP);
                CustomeLine line = *linesIterator;
                double x = CGAL::to_double(line.getQ().x());
                double y = CGAL::to_double(line.getQ().y());
                glVertex2d(transformX(x, width), transformY(y, height));

                x = CGAL::to_double(line.getP().x());
                y = CGAL::to_double(line.getP().y());
                glVertex2d(transformX(x, width), transformY(y, height));
            glEnd();
        }

        for (std::vector<vector<PointForConvexHull> >::iterator it = results.begin(); it != results.end(); ++it) {
            //qDebug() << "SIZE " << (*it).size();
            glColor3f(0.03, 0.392, 0.392);
            glBegin(GL_LINE_LOOP);
            for (std::vector<PointForConvexHull>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
                double x = (*it2).x();
                double y = (*it2).y();
                //qDebug() << x << " " << y;//(*it).size();
                //glVertex2d(transformX(x, width), transformY(y, height));
                glVertex2d(x, y);
            }
            glEnd();
        }
    }
    /***End Draw Connecting Lines***/
}

void GLWidget::update() {
    QWidget::update();
}

void GLWidget::generateXfigFile(QString filepath) {
    XfigFileGenerator fileGenerator(filepath);

    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
    fileGenerator.drawPolygons(polygons);

    QList<PointToCluster>* polygonsPoints = Context::getInstance()->computePointsForClustering();
//    if (Context::getInstance()->isVerticesEnabled()) {
//        QList<CustomPoint>::iterator pointsIterator;
//        for ( pointsIterator = polygonsPoints->begin(); pointsIterator != polygonsPoints->end(); pointsIterator++) {
//            glVertex2d(transformX(CGAL::to_double((*pointsIterator).x()), width), transformY(CGAL::to_double((*pointsIterator).y()), height));
//        }
//    }


    if (Context::getInstance()->isDrawConnectingLines()) {
        std::vector<std::vector<PointForConvexHull> > results;
        Context::getInstance()->getConvexHullComputationalUtil()->compute(Context::getInstance()->getFileReader().constructPolygons(), results);

        QList<CustomeLine>::iterator linesIterator;
        QList<CustomeLine> connectingLines = Context::getInstance()->getConnectingLines();

        for (linesIterator = connectingLines.begin(); linesIterator != connectingLines.end(); linesIterator++) {
            CustomeLine line = *linesIterator;
            double x1 = CGAL::to_double(line.getQ().x());
            double y1 = CGAL::to_double(line.getQ().y());

            //glVertex2d(transformX(x, width), transformY(y, height));

            double x2 = CGAL::to_double(line.getP().x());
            double y2 = CGAL::to_double(line.getP().y());
            //glVertex2d(transformX(x, width), transformY(y, height));

            fileGenerator.drawLine(x1, y1, x2, y2, false);
        }

//        for (std::vector<vector<PointForConvexHull> >::iterator it = results.begin(); it != results.end(); ++it) {
//            glColor3f(0, 1, 1);
//            glBegin(GL_LINE_LOOP);
//            for (std::vector<PointForConvexHull>::iterator it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
//                double x = (*it2).x();
//                double y = (*it2).y();

//                glVertex2d(x, y);
//            }
//        }
    }

    /***Draw Voronoi Diagram*****/
    if (Context::getInstance()->isVerticesEnabled() && Context::getInstance()->isDrawVoronoi()) {
        VDUtil vdUtil;
        vdUtil.construct(*polygonsPoints, !Context::getInstance()->isDrawOnlyNonIntersectingVoronoiEdges());
        QList<CustomPoint> voronoiLineSegments = vdUtil.getVoronoiLineSegments();

        fileGenerator.drawLines(voronoiLineSegments, false);
        if (!Context::getInstance()->isDrawOnlyNonIntersectingVoronoiEdges()) {
            QList<CustomPoint> intersectingVoronoiLineSegments = vdUtil.getIntersectingVoronoiLineSegments();
            fileGenerator.drawLines(intersectingVoronoiLineSegments, true);
        }
    }
    /***End Draw Voronoi Diagram*****/

}

void GLWidget::mousePressEvent(QMouseEvent *event){
    bool disableConnectingLines = false;
    double x = event->x();
    double y = this->flipY(event->y(), height());
    Context::getInstance()->setCurrentX(x);
    Context::getInstance()->setCurrentY(y);
    int selectedVertexIndex = Context::getInstance()->getFileReader().hasVertex(Context::getInstance()->getSelectedPolygon(), x, y);
    this->getSelectedPolygon(x, y);

    switch (Context::getInstance()->getEditMode()) {
        case Constants::ADD_VERTEX_MODE:
            if (Context::getInstance()->getFileReader().insertVertex(Context::getInstance()->getSelectedPolygon(), x, y)) {
                disableConnectingLines = true;
                Context::getInstance()->setDrawConnectingLines(false);
            }
            break;
        case Constants::DELETE_VERTEX_MODE:
            if (Context::getInstance()->getFileReader().removeVertex(Context::getInstance()->getSelectedPolygon(), selectedVertexIndex, x, y)) {
                disableConnectingLines = true;
                Context::getInstance()->setDrawConnectingLines(false);
            }
            break;
        case Constants::EDIT_MODE:
            //Context::getInstance()->getFileReader().insertVertex(i, x, y);
            break;
        case Constants::NORMAL_MODE:
            break;
        case Constants::CREATE_POLYGONS_MODE:
            this->pushVertexToNewPolygon(x, y);
            break;
        default:
            break;
    }

    emit hadMousePress(x, y, disableConnectingLines);
}

void GLWidget::pushVertexToNewPolygon(double x, double y) {
    bool first = false;
    if (this->newPolygon == NULL) {
        this->newPolygon = new CustomPolygon();
        first = true;
    }
    if ( x >= oldX - Constants::DELTA && x <= oldX + Constants::DELTA &&
          y >= oldY - Constants::DELTA && y <= oldY + Constants::DELTA) {
         Context::getInstance()->getFileReader().insertPolygon(*(this->newPolygon));
         this->newPolygon = NULL;
    } else {
        this->newPolygon->push_back(*(new Point(x, y)));

    if (first) {
    oldX = x;
    oldY = y;
    }
}
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    if (Context::getInstance()->getEditMode() == Constants::EDIT_MODE || Context::getInstance()->getEditMode() == Constants::MOVE_MODE || Context::getInstance()->getEditMode() == Constants::ADD_VERTEX_MODE) {
        Context::getInstance()->setDrawConnectingLines(false);
        int selectedVertexIndex = Context::getInstance()->getFileReader().hasVertex(Context::getInstance()->getSelectedPolygon(), event->x(), this->flipY(event->y(), height()));

        if ( Context::getInstance()->isPolygonSelected()) {
            //qDebug() << "clicked on the vertex";
            if (Context::getInstance()->getEditMode() == Constants::MOVE_MODE) {
                double deltaX = Context::getInstance()->getCurrentX() - event->x();
                double deltaY = Context::getInstance()->getCurrentY() - this->flipY(event->y(), height());
                Context::getInstance()->getFileReader().movePolygon(Context::getInstance()->getSelectedPolygon(), deltaX, deltaY);
                Context::getInstance()->setCurrentX(Context::getInstance()->getCurrentX() - deltaX);
                Context::getInstance()->setCurrentY(Context::getInstance()->getCurrentY() - deltaY);
            } else if (selectedVertexIndex > -1) {
                Context::getInstance()->getFileReader().updateSelectedPolygonVertex(Context::getInstance()->getSelectedPolygon() ,selectedVertexIndex, event->x(), this->flipY(event->y(), height()));
            }
            this->update();

        }
        emit hadMouseMove(event->x(), this->flipY(event->y(), height()));
    }
}

double GLWidget::transformX(double x, double width) {
    double transformed = (x * 1.0 - width)/width;
    transformed = x * 1.0 / width;
    return transformed * 2 - 1;
}

double GLWidget::transformY(double y, double height) {
    double transformed = (y * 1.0 - height)/height;
    transformed = y * 1.0 / height;
    return transformed * 2 - 1;
}

void GLWidget::getSelectedPolygon(double x, double y) {
    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();

    int i = 0;
    for (QList<CustomPolygon>::iterator iter = polygons.begin(); iter != polygons.end(); iter++, i++) {
        CGAL::Bounded_side positionOfPointInPolygon = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(*iter, x, y);
        if(positionOfPointInPolygon != CGAL::ON_UNBOUNDED_SIDE) {
            Context::getInstance()->setSelectedPolygon(i);
            this->selectedPolygon = *iter;

            //if(positionOfPointInPolygon == CGAL::ON_BOUNDARY) { //this could be eliminated
                //TODO if clicked on vertex then don't insert
                //Context::getInstance()->getFileReader().insertVertex(i, x, y);

            //}
            return;
        }
    }
    Context::getInstance()->setSelectedPolygon(-1); // no selection
}

double GLWidget::flipY(double y, double height) {
    return height - y;
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
}
