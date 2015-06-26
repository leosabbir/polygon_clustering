#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

class GLWidget : public QGLWidget {

    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    //~GLWidget();
    void initiallizeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void update();

    double transformX(double x, double width);
    double transformY(double y, double height);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

signals:
    void hadMousePress();

    void hadMouseMove();

};

#endif // GLWIDGET_H
