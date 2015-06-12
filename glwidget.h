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

    double transformX(int x, int width);
    double transformY(int y, int height);
};

#endif // GLWIDGET_H
