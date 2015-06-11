#include "glwidget.h"
#include <iostream>
#include <GL/glut.h>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {
}

void GLWidget::initiallizeGL(){
    glClearColor(0.2, 0.2, 0.2, 1);

}

void GLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "Printing..." << std::endl;
    std::cout << size().height() << std::endl;
    std::cout << size().width() << std::endl;

    double width = size().width();
    double height = size().height();

    //glutWireTeapot(0.6);
    glBegin(GL_LINE_LOOP);
        glColor3f(1, 0, 0);
        //glVertex3f(-0.5, -0.5, 0);
        //glColor3f(0, 1, 0);
        //glVertex3f( 0.5, -0.5, 0);
        //glColor3f(0, 0, 1);
        //glVertex3f( 0, 0.5, 0);
    //glVertex2f( .9,  0);
    //glVertex2i( -1,  0);
    glVertex2f( 0,  0);
    glVertex2f( 0,  .5);
    glVertex2f( .05,  0.7);
    glVertex2f( 0.07,  0.6);
    glVertex2f( 0.5,  0.05);
    glVertex2f( .9,  .5);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glColor3f(1, 0, 0);
    glVertex2f( -750,  -550);
    glVertex2f( 0,  .5);
    glVertex2f( .05,  0.7);
    glVertex2f( 0.07,  0.6);
    glVertex2f( 0.5,  0.05);
    glVertex2f( .9,  .5);
    glEnd();
}

void GLWidget::resizeGL(int w, int h) {
    glViewport(0, 0, (GLint) w, (GLint) h);
}

