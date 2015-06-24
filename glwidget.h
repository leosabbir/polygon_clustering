#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget
{
public:
    explicit GLWidget(QWidget *parent = 0);

    void initiallizeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void update();

    double transformX(double x, double width);
    double transformY(double y, double height);
};

#endif // GLWIDGET_H
