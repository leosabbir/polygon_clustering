#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <boost/lambda/lambda.hpp>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include "GL/freeglut.h"
#include "GL/gl.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_thresholdSlider_sliderMoved(int position);

    void on_thresholdSlider_valueChanged(int value);

    void on_applyBtn_released();

    void onMouseEvent();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
