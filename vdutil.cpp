#include "vdutil.h"

#include <iostream>
#include <QDebug>
#include "context.h"


//A class to recover Voronoi diagram from stream.
//Rays, lines and segments are cropped to a rectangle
//so that only segments are stored
struct Cropped_voronoi_from_delaunay{
  std::list<Segment_2> m_cropped_vd;
  Iso_rectangle_2 m_bbox;

  Cropped_voronoi_from_delaunay(const Iso_rectangle_2& bbox):m_bbox(bbox){}

  template <class RSL>
  void crop_and_extract_segment(const RSL& rsl){
    CGAL::Object obj = CGAL::intersection(rsl,m_bbox);
    const Segment_2* s=CGAL::object_cast<Segment_2>(&obj);
    if (s) m_cropped_vd.push_back(*s);
  }

  void operator<<(const Ray_2& ray)    { crop_and_extract_segment(ray); }
  void operator<<(const Line_2_Voronoi& line)  { crop_and_extract_segment(line); }
  void operator<<(const Segment_2& seg){ crop_and_extract_segment(seg); }
};

VDUtil::VDUtil() {
    voronoiLineSegments = NULL;
    intersectingVoronoiLineSegments = NULL;
}

void VDUtil::construct(QList<PointToCluster> vertices, bool constructWithoutIntersectingEdges) {
    if (voronoiLineSegments == NULL) {
        this->voronoiLineSegments = new QList<CustomPoint>();
        this->intersectingVoronoiLineSegments  = new QList<CustomPoint>();
    } else {
        this->voronoiLineSegments->clear();
        this->intersectingVoronoiLineSegments->clear();
    }

    Delaunay_triangulation_2 dt2;
    std::vector<Point_2_Voronoi> points;

    for ( QList<PointToCluster>::iterator vertexIterator = vertices.begin(); vertexIterator != vertices.end(); vertexIterator++) {
        //qDebug() << CGAL::to_double((*vertexIterator).x()) <<  " : " << CGAL::to_double((*vertexIterator).y());
        points.push_back(Point_2_Voronoi(CGAL::to_double((*vertexIterator).x()), CGAL::to_double((*vertexIterator).y())));
    }

    dt2.insert(points.begin(), points.end());
    Iso_rectangle_2 bbox(0,0,800,600);
    Cropped_voronoi_from_delaunay vor(bbox);
    dt2.draw_dual(vor);

    //print the cropped Voronoi diagram as segments
    //std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
    //std::ostream_iterator<Segment_2>(std::cout,"\n"));

      std::list<Segment_2>::const_iterator iterator;
      //std::cout << vor.m_cropped_vd.size() << std::endl;
      for (iterator = vor.m_cropped_vd.begin(); iterator != vor.m_cropped_vd.end(); ++iterator) {
          double x1 = (*iterator).source().x();
          double y1 = (*iterator).source().y();

          double x2 = (*iterator).target().x();
          double y2 = (*iterator).target().y();

          //correct nan
          if (x1 != x1 || x2 != x2 || y1 == !y1 || y2 == !y2) {
              continue;
          }
          CustomPoint *p = new CustomPoint(x1, y1);
          CustomPoint *q = new CustomPoint(x2, y2);

          if (constructWithoutIntersectingEdges) {
              QList<CustomPolygon> polygons = Context::getInstance()->getFileReader().constructPolygons();
              bool intersects = false;
              for (int k = 0; k < polygons.size(); k++) {
                  CGAL::Bounded_side positionOfPointInPolygon1 = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(polygons.at(k), x1, y1);
                  CGAL::Bounded_side positionOfPointInPolygon2 = Context::getInstance()->getCgalUtility().getPointLocationOnPolygon(polygons.at(k), x2, y2);
                  if(positionOfPointInPolygon1 == CGAL::ON_UNBOUNDED_SIDE && positionOfPointInPolygon2 == CGAL::ON_UNBOUNDED_SIDE) {
                      for ( Vertex_iterator vertexIterator = polygons.at(k).vertices_begin(); vertexIterator != polygons.at(k).vertices_end(); vertexIterator++) {
                          double x3 = CGAL::to_double((*vertexIterator).x());
                          double y3 = CGAL::to_double((*vertexIterator).y());
                          double x4, y4;
                          if (vertexIterator + 1 == polygons.at(k).vertices_end()) {
                            x4 = CGAL::to_double(polygons.at(k).vertices_begin()->x());
                            y4 = CGAL::to_double(polygons.at(k).vertices_begin()->y());
                          } else {
                            x4 = CGAL::to_double((*(vertexIterator+1)).x());
                            y4 = CGAL::to_double((*(vertexIterator+1)).y());
                          }

                          if (this->doesIntersect(x1, y1, x2, y2, x3, y3, x4, y4)) {
                              intersects = true;
                              break;
                          }
                      }
                      if (intersects) {
                          break;
                      }
                  } else if((positionOfPointInPolygon1 == CGAL::ON_BOUNDED_SIDE || positionOfPointInPolygon1 == CGAL::ON_BOUNDARY) ||
                          (positionOfPointInPolygon2 == CGAL::ON_BOUNDED_SIDE || positionOfPointInPolygon2 == CGAL::ON_BOUNDARY)) {
                      intersects = true;
                      break;
                  }

              }
              if ( !intersects ) {
                  this->voronoiLineSegments->append(*p);
                  this->voronoiLineSegments->append(*q);
              } else {
                  this->intersectingVoronoiLineSegments->append(*p);
                  this->intersectingVoronoiLineSegments->append(*q);
              }
            //qDebug() << (*iterator).target().x() << " : " << (*iterator).target().y();
          } else {
              this->voronoiLineSegments->append(*p);
              this->voronoiLineSegments->append(*q);
          }
      }
}

bool VDUtil::doesIntersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4) {
    double area = x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
    int turn = 0;

    if (area >= 0) {
        turn = 1;
    } else {
        turn = -1;
    }

    area = x1 * (y2 - y4) + x2 * (y4 - y1) + x4 * (y1 - y2);

    if ((turn == 1 && area >= 0) || (turn == -1 && area < 0)) {
        return false;
    } else {
        area = x3 * (y4 - y2) + x4 * (y2 - y3) + x2 * (y3 - y4);

        if (area >= 0) {
            turn = 1;
        } else {
            turn = -1;
        }

        area = x3 * (y4 - y1) + x4 * (y1 - y3) + x1 * (y3 - y4);
        if ((turn == 1 && area >= 0) || (turn == -1 && area < 0)) {
            return false;
        } else {
            return true;
        }
    }
}

QList<CustomPoint> VDUtil::getVoronoiLineSegments() {
    return *(this->voronoiLineSegments);
}

QList<CustomPoint> VDUtil::getIntersectingVoronoiLineSegments() {
    return *(this->intersectingVoronoiLineSegments);
}
