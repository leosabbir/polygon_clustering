#include "mainwindow.h"
#include <QtGui>
#include <GL/glut.h>
#include <QApplication>
#include "plygoncontainer.h"
#include "polytopedistance.h"

//#include <CGAL/Cartesian.h>
//#include <CGAL/Polygon_2.h>
//#include <CGAL/point_generators_2.h>
//#include <CGAL/random_convex_set_2.h>
//#include <CGAL/all_furthest_neighbors_2.h>
//#include <CGAL/IO/Ostream_iterator.h>
//#include <iostream>
//#include <vector>
//typedef double                                    FT;
//typedef CGAL::Cartesian<FT>                       Kernel;
//typedef Kernel::Point_2                           Point;
//typedef std::vector<int>                          Index_cont;
//typedef CGAL::Polygon_2<Kernel>                   Polygon_2;
//typedef CGAL::Random_points_in_square_2<Point>    Generator;
//typedef CGAL::Ostream_iterator<int,std::ostream>  Oiterator;


void renderFunction()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glBegin(GL_POLYGON);
        glVertex2f(-0.5, -0.5);
        glVertex2f(-0.5, 0.5);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.5, -0.5);
    glEnd();
    glFlush();
}

/* Main method - main entry point of application
the freeglut library does the window creation work for us,
regardless of the platform. */
/*
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("OpenGL - First window demo");
    glutDisplayFunc(renderFunction);
    glutMainLoop();
    return 0;
}
*/


int main(int argc, char *argv[])
{
//    Polygon_2 p;
//      CGAL::random_convex_set_2(10, std::back_inserter(p), Generator(1));

//      // compute all furthest neighbors:
//        CGAL::all_furthest_neighbors_2(p.vertices_begin(), p.vertices_end(),
//                                       Oiterator(std::cout));
//        std::cout << std::endl;

    PolytopeDistance pp;
    pp.computeDistance();

    glutInit(&argc, argv);
    QApplication a(argc, argv);
    MainWindow w;
    //PlygonContainer w;
    //w.draw();
    w.show();

    return a.exec();
}

