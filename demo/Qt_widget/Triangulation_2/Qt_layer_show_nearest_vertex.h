// ============================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// Every use of CGAL requires a license. 
//
// Academic research and teaching license
// - For academic research and teaching purposes, permission to use and copy
//   the software and its documentation is hereby granted free of charge,
//   provided that it is not a component of a commercial product, and this
//   notice appears in all copies of the software and related documentation. 
//
// Commercial licenses
// - Please check the CGAL web site http://www.cgal.org/index2.html for 
//   availability.
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_layer_show_nearest_vertex.h
// package       : Qt_widget
// author(s)     : Radu Ursu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_LAYER_SHOW_NEAREST_VERTEX_H
#define CGAL_QT_LAYER_SHOW_NEAREST_VERTEX_H

#include <CGAL/IO/Qt_widget_layer.h>
#include <qobject.h>


namespace CGAL {

template <class T>
class Qt_layer_nearest_vertex : public Qt_widget_layer
{
public:
  typedef typename T::Point			Point;
  typedef typename T::Segment			Segment;
  typedef typename T::Face_handle		Face_handle;
  typedef typename T::Vertex_handle		Vertex_handle;
  typedef typename T::Geom_traits::FT		FT;

  Qt_layer_nearest_vertex(T &t) : tr(t), first_time(TRUE) {};
	
  void draw(){first_time = TRUE;};
  void mouseMoveEvent(QMouseEvent *e)
  {
    if (tr.dimension()<1) return;
    FT
      x=static_cast<FT>(widget->x_real(e->x())),
      y=static_cast<FT>(widget->y_real(e->y()));
    Point p(x, y);
    RasterOp old = widget->rasterOp();	//save the initial raster mode
    widget->setRasterOp(XorROP);
    widget->lock();
    *widget << Point(10, 10);
    Vertex_handle v = tr.nearest_vertex(p);
    *widget << CGAL::GREEN << CGAL::PointSize (10)
		<< CGAL::PointStyle (CGAL::CIRCLE);
    if(!first_time)
      *widget << oldPoint;	
    *widget << v->point();
    widget->unlock();
    widget->setRasterOp(old);
    oldPoint = v->point();
    first_time = FALSE;
  };
  void leaveEvent(QEvent *e)
  {
    widget->lock();
    RasterOp old = widget->rasterOp();	//save the initial raster mode
    widget->setRasterOp(XorROP);
    *widget << CGAL::GREEN << CGAL::PointSize (10) 
		<< CGAL::PointStyle (CGAL::CIRCLE);
    *widget << oldPoint;	
    widget->unlock();
    widget->setRasterOp(old);
    first_time = TRUE;
    //remove_leftovers(widget);
  }

private:
	T       &tr;
	Point		oldPoint,
          newPoint;											;
	bool		first_time;
	
};//end class 

} // namespace CGAL

#endif // CGAL_QT_LAYER_SHOW_NEAREST_VERTEX_H
