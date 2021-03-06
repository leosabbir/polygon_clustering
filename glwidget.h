#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include "custompolygon.h"
#include "constants.h"
#include "utils.h"
#include "xfigfilegenerator.h"

class GLWidget : public QGLWidget {

    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);

    //~GLWidget();
    void initiallizeGL();
    void paintGL();
    void resizeGL(int w, int h);
    void update();

    void generateXfigFile(QString filepath);

    double transformX(double x, double width);
    double transformY(double y, double height);
    double flipY(double y, double height);

    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    void getSelectedPolygon(double x, double y);

    void pushVertexToNewPolygon(double x, double y);

signals:
    void hadMousePress(int x, int y, bool disableConnectingLines);

    void hadMouseMove(int x, int y);

private:
    CustomPolygon selectedPolygon;
    CustomPolygon *newPolygon;
    double oldX, oldY;

};

#endif // GLWIDGET_H
