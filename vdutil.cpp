#include "vdutil.h"

#include <iostream>
#include <QDebug>


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
}

//void VDUtil::printEndPoint(Halfedge_handle e, bool isSrc) {
//        std::cout << "\t";
//      if ( isSrc ) {
//        if ( e->has_source() )  std::cout << e->source()->point() << std::endl;
//        else  std::cout << "point at infinity" << std::endl;
//      } else {
//        if ( e->has_target() )  std::cout << e->target()->point() << std::endl;
//        else  std::cout << "point at infinity" << std::endl;
//      }
//}

void VDUtil::construct(QList<CustomPoint> vertices) {

//    VD vd;

////    Site_2 site;
////    vd.insert(site);
//    int ns = 0;
//    int nr = 0;
//    for ( QList<CustomPoint>::iterator vertexIterator = vertices.begin(); vertexIterator != vertices.end(); vertexIterator++) {
//        vd.insert(*(new Site_2(CGAL::to_double((*vertexIterator).x()), CGAL::to_double((*vertexIterator).y()))));
//    }
//    Edge_Iterator eit ;
//    for ( eit = vd.edges_begin(); eit != vd.edges_end(); ++eit ) {
//        // Get a vertex from the edge
////            DT::Face& f = *(eit->first);
////            int i = eit->second;
////            Vertex_handle vs = f.vertex(f.cw(i));
////            Vertex_handle vt = f.vertex(f.ccw(i));

//        //DT::Segment seg = vd.segment(*eit);
//        if ( eit -> is_ray()) {
//            nr ++;
//        } else {
//            ns ++;
//        }
//    }
//    std::cout << ns << " : " << nr << std::endl;
}

void VDUtil::construct2(QList<CustomPoint> vertices) {
    if (voronoiLineSegments == NULL) {
        this->voronoiLineSegments = new QList<CustomPoint>();
    } else {
        this->voronoiLineSegments->clear();
    }

    Delaunay_triangulation_2 dt2;
    std::vector<Point_2_Voronoi> points;

    for ( QList<CustomPoint>::iterator vertexIterator = vertices.begin(); vertexIterator != vertices.end(); vertexIterator++) {
        qDebug() << CGAL::to_double((*vertexIterator).x()) <<  " : " << CGAL::to_double((*vertexIterator).y());
        points.push_back(Point_2_Voronoi(CGAL::to_double((*vertexIterator).x()), CGAL::to_double((*vertexIterator).y())));
    }

    dt2.insert(points.begin(), points.end());
    Iso_rectangle_2 bbox(0,0,800,600);
    Cropped_voronoi_from_delaunay vor(bbox);
    dt2.draw_dual(vor);

    //print the cropped Voronoi diagram as segments
//      std::copy(vor.m_cropped_vd.begin(),vor.m_cropped_vd.end(),
//        std::ostream_iterator<Segment_2>(std::cout,"\n"));

      std::list<Segment_2>::const_iterator iterator;
      //std::cout << vor.m_cropped_vd.size() << std::endl;
      for (iterator = vor.m_cropped_vd.begin(); iterator != vor.m_cropped_vd.end(); ++iterator) {
          qDebug() << (*iterator).source().x() << " : " << (*iterator).source().y();
          this->voronoiLineSegments->append(*(new CustomPoint((*iterator).source().x(), (*iterator).source().y())));
          qDebug() << (*iterator).target().x() << " : " << (*iterator).target().y();
          this->voronoiLineSegments->append(*(new CustomPoint((*iterator).target().x(), (*iterator).target().y())));
      }
}

QList<CustomPoint> VDUtil::getVoronoiLineSegments() {
    return *(this->voronoiLineSegments);
}
