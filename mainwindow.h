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
    void initializeEditModes();
    void adaptSelectedAlgorithmMode(int index);

private slots:
    void on_thresholdSlider_sliderMoved(int position);

    void on_thresholdSlider_valueChanged(int value);

    void on_applyBtn_released();

    void onMouseEvent(int x, int y, bool disableConnectingLines);

    void onMouseMoveEvent(int x, int y);

    void on_editModeComboBox_currentIndexChanged(int index);

    void on_createBtn_released();

    void on_openBtn_released();

    void on_saveBtn_released();

    void on_saveasBtn_released();

    void on_clearBtn_released();

    void on_borderChkBox_released();

    void on_verticesChkBox_released();

    void on_showAllEdgesChkBox_released();

    void on_xfigFileBtn_released();

    void on_algoMode_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
