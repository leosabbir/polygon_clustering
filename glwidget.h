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
};

#endif // GLWIDGET_H
