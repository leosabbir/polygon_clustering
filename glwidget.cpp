#include "glwidget.h"
#include <iostream>
#include <GL/glut.h>
#include <QList>
#include <QPoint>
#include <dummydata.h>
#include "inputfilereader.h"
#include "context.h"
#include "customeline.h"

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
    Constants::WIDTH = this->size().width();
    Constants::HEIGHT = this->size().height();
    //this->selectedPolygon = NULL;
    //setMouseTracking(true); // if this is set, then mouse movement will be tracked even if not pressed
}

//GLWidget::~GLWidget() {

//}

void GLWidget::initiallizeGL(){
    glClearColor(0.2, 0.2, 0.2, 1);

}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);

    double width = Constants::WIDTH = size().width();
    double height = Constants::HEIGHT = size().height();

    //glutWireTeapot(0.6);
    glColor3f(1, 0, 0);

    /****/
    int i = 0;
    QList<CustomPolygon>::iterator polygonIterator;
    QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
    for ( polygonIterator = polygons.begin(); polygonIterator != polygons.end() ; polygonIterator++) {
        glLineWidth(2);
        glBegin(GL_LINE_LOOP);
        bool isSelectedPolygon = i++ == Context::getInstance()->getSelectedPolygon();
        if (isSelectedPolygon) {
            glColor3f(0, 0, 1);
        } else {
            glColor3f(1, 0, 0);
        }

        for ( Vertex_iterator vertexIterator = (*polygonIterator).vertices_begin(); vertexIterator != (*polygonIterator).vertices_end(); vertexIterator++) {
            glVertex2d(transformX(CGAL::to_double((*vertexIterator).x()), width), transformY(CGAL::to_double((*vertexIterator).y()), height));
        }
        glEnd();
        if (isSelectedPolygon) {
            glColor3f(1, 1, 1);
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
    /****/

    /***Draw Connecting Lines***/
    if (Context::getInstance()->isDrawConnectingLines()) {
        glColor3f(0, 1, 0);
        glLineWidth(1);
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
    }
    /***End Draw Connecting Lines***/
}

void GLWidget::update() {
    QWidget::update();
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
        default:
            break;
    }

    emit hadMousePress(x, y, disableConnectingLines);
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
