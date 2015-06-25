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

void GLWidget::mousePressEvent(QMouseEvent *){
    qDebug() << "mouse pressed";
    emit hadMousePress();
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

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
}

