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
    //std::cout << "Painting..." << std::endl;
    //std::cout << size().height() << std::endl;
    //std::cout << size().width() << std::endl;

    double width = size().width();
    double height = size().height();

    //glutWireTeapot(0.6);
    glColor3f(1, 0, 0);

    QList< QList<QPoint> >::iterator polygonIterator;
//    InputFileReader fileReader;
//    fileReader.constructPolygons();Context
    QList< QList<QPoint> > polygons = Context::getInstance()->getFileReader().getUiPolygons();//DummyData().getPolygons();
    for ( polygonIterator = polygons.begin(); polygonIterator != polygons.end() ; polygonIterator++) {
        glBegin(GL_LINE_LOOP);
        QList<QPoint>::iterator vertexIterator;
        for ( vertexIterator = (*polygonIterator).begin(); vertexIterator != (*polygonIterator).end(); vertexIterator++) {
            QPoint vertex = *vertexIterator;
            glVertex2d(transformX(vertex.x(), width), transformY(vertex.y(), height));
        }
        glEnd();
    }

    //if ( this->selectedPolygon != NULL) {
        glColor3f(0, 0, 1);
        glBegin(GL_LINE_LOOP);
        for ( Vertex_iterator vertexIterator = this->selectedPolygon.vertices_begin(); vertexIterator != this->selectedPolygon.vertices_end(); vertexIterator++) {
            //qDebug() << CGAL::to_double((*vertexIterator).x());
            glVertex2d(transformX(CGAL::to_double(((*vertexIterator)).x()), width), transformY(CGAL::to_double(((*vertexIterator)).y()), height));
        }
        glEnd();
    //}

    glColor3f(0, 1, 0);
    QList<CustomeLine>::iterator linesIterator;
    QList<CustomeLine> connectingLines = Context::getInstance()->getConnectingLines();
    //std::cout << connectingLines.size() << " lines in the list" << std::endl;
    for (linesIterator = connectingLines.begin(); linesIterator != connectingLines.end(); linesIterator++) {
        glBegin(GL_LINE_LOOP);
            CustomeLine line = *linesIterator;
            double x = CGAL::to_double(line.getQ().x());
            double y = CGAL::to_double(line.getQ().y());
            //std::cout << "Drawing line for " << x << "," << y << std::endl;
            glVertex2d(transformX(x, width), transformY(y, height));

            x = CGAL::to_double(line.getP().x());
            y = CGAL::to_double(line.getP().y());
            //std::cout << "Drawing line for " << x << "," << y << std::endl;
            glVertex2d(transformX(x, width), transformY(y, height));
        glEnd();
    }

}

void GLWidget::update() {
    QWidget::update();
}

void GLWidget::mousePressEvent(QMouseEvent *event){
    emit hadMousePress(event->x(), this->flipY(event->y(), height()));
}

void GLWidget::mouseMoveEvent(QMouseEvent *event) {
    emit hadMouseMove(event->x(), this->flipY(event->y(), height()));
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

    for (QList<CustomPolygon>::iterator iter = polygons.begin(); iter != polygons.end(); iter++) {
        if(Context::getInstance()->getCgalUtility().isInside(*iter, x, y)) {
            qDebug() << true;
            this->selectedPolygon = (*iter);
            //return this->selectedPolygon;
        }
    }

    //return NULL;
}

double GLWidget::flipY(double y, double height) {
    return height - y;
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
}

