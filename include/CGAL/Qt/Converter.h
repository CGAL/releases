// Copyright (c) 2008  GeometryFactory Sarl (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/GraphicsView/include/CGAL/Qt/Converter.h $
// $Id: Converter.h 47047 2008-11-26 13:08:15Z lrineau $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>
#ifndef CGAL_QT_CONVERTER_H
#define CGAL_QT_CONVERTER_H

#include <QPointF>
#include <QLineF>
#include <QRectF>
#include <QPolygonF>
#include <list>

#include <CGAL/intersection_2.h>
#include <CGAL/auto_link/Qt4.h>

namespace CGAL {

template <typename K>
class Circular_arc_point_2;

namespace Qt {


template <typename K>
class Converter {

  bool clippingRectIsInitialized;
  CGAL::Iso_rectangle_2<K> clippingRect;

public:

  Converter()
    : clippingRectIsInitialized(false)
  {
  }

  Converter(QRectF rect)
  {
    if(rect.isValid()) {
      clippingRect = this->operator()(rect);
      clippingRectIsInitialized = true;
    }
    else
      clippingRectIsInitialized = false;
  }

  CGAL::Point_2<K> operator()(const QPointF& qp) const
  {
    return CGAL::Point_2<K>(qp.x(), qp.y());
  }


  QPointF operator()(const CGAL::Point_2<K>& p) const
  {
    return QPointF(to_double(p.x()), to_double(p.y()));
  }

  QPointF operator()(const CGAL::Circular_arc_point_2<K>& p) const
  {
    return QPointF(to_double(p.x()), to_double(p.y()));
  }

      
  CGAL::Segment_2<K> operator()(const QLineF& qs) const
  {
    return CGAL::Segment_2<K>(operator()(qs.p1()), operator()(qs.p2));
  }
 
  QLineF operator()(const CGAL::Segment_2<K> &s) const
  {
    return QLineF(operator()(s.source()), operator()(s.target()));
  }

  
  CGAL::Iso_rectangle_2<K> operator()(const QRectF& qr) const
  {
    return CGAL::Iso_rectangle_2<K>(operator()(qr.bottomLeft()), operator()(qr.topRight()));
  }


  QRectF operator()(const CGAL::Iso_rectangle_2<K>& r) const
  {
    return QRectF(operator()(r[3]), operator()(r[1]));  // top left, bottom right
  }


  QRectF operator()(const CGAL::Bbox_2& bb)
  {
    return QRectF(bb.xmin(),
		  bb.ymin(),
		  bb.xmax()-bb.xmin(),
		  bb.ymax()-bb.ymin());
  }

     
  QLineF operator()(const CGAL::Ray_2<K> &r) const
  {
    CGAL_assertion(clippingRectIsInitialized);
    Object o = CGAL::intersection(r, clippingRect);
    typedef CGAL::Segment_2<K> Segment_2;
    typedef CGAL::Point_2<K> Point_2;
    if(const Segment_2 *s = CGAL::object_cast<Segment_2>(&o)){
      return this->operator()(*s);
    } else if(const Point_2 *p = CGAL::object_cast<Point_2>(&o)){
      return QLineF(operator()(*p), operator()(*p));
    }
    return QLineF();
  }

  QLineF operator()(const CGAL::Line_2<K> &l) const
  {
    CGAL_assertion(clippingRectIsInitialized);
    Object o = CGAL::intersection(l, clippingRect);
    typedef CGAL::Segment_2<K> Segment_2;
    typedef CGAL::Point_2<K> Point_2;
    if(const Segment_2 *s = CGAL::object_cast<Segment_2>(&o)){
      return this->operator()(*s);
    } else if(const Point_2 *p = CGAL::object_cast<Point_2>(&o)){
      return QLineF(operator()(*p), operator()(*p));
    }
    return QLineF();
  }

  QPolygonF operator()(const CGAL::Triangle_2<K> &t)
  {
    QPolygonF qp;
    qp << operator()(t.vertex(0)) << operator()(t.vertex(1)) << operator()(t.vertex(2));
    return qp;
  }


  void operator()(std::list< CGAL::Point_2<K> >& p, const QPolygonF& qp) const
  {
    for(int i = 0; i < qp.size(); i++){
      p.push_back(operator()(qp[i]));
    }
  }

};

} // namesapce Qt
} // namespace CGAL
#endif // CGAL_QT_CONVERTER_H
