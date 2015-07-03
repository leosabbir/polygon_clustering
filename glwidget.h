#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "custompolygon.h"
#include "constants.h"
#include "utils.h"

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
    double flipY(double y, double height);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    void getSelectedPolygon(double x, double y);

signals:
    void hadMousePress(int x, int y, bool disableConnectingLines);

    void hadMouseMove(int x, int y);

private:
    CustomPolygon selectedPolygon;

};

#endif // GLWIDGET_H
