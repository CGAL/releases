// ======================================================================
//
// Copyright (c) 1997-2000 The CGAL Consortium

// Copyright (c) 2002 ENS de Paris
//
// This software and related documentation are part of the Computational
// Geometry Algorithms Library (CGAL).
// This software and documentation are provided "as-is" and without warranty
// of any kind. In no event shall the CGAL Consortium be liable for any
// damage of any kind. 
//
// The Qt widget we provide for CGAL is distributed under the QPL,
// which is Trolltech's open source license. For more information see 
//     http://www.trolltech.com/developer/licensing/qpl.html
//
// The CGAL Consortium consists of Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbrucken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).
//
// ----------------------------------------------------------------------
//
// file          : include/CGAL/IO/Qt_widget_get_line.h
// package       : Qt_widget (1.2.30)
// author(s)     : Ursu Radu
// release       : CGAL-2.4
// release_date  : 2002, May 16
//
// coordinator   : Laurent Rineau
//
// email         : contact@cgal.org
// www           : http://www.cgal.org
//
// ======================================================================

#ifndef CGAL_QT_WIDGET_GET_LINE_H
#define CGAL_QT_WIDGET_GET_LINE_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include <qcursor.h>

#ifndef CGAL_QT_WIDGET_GET_POINT_BUTTON
#define CGAL_QT_WIDGET_GET_POINT_BUTTON Qt::LeftButton
#endif


namespace CGAL {

template <class R>
class Qt_widget_get_line : public Qt_widget_layer
{
public:
  typedef typename R::Point_2  Point;
  typedef typename R::Line_2	  Line;
  typedef typename	R::FT FT;

  Qt_widget_get_line() : firstpoint(false), 
			 firsttime(true){};
  void draw(){
    firsttime = true;
  }
private:
  QCursor oldcursor;

  bool is_pure(Qt::ButtonState s){
    if((s & Qt::ControlButton) ||
       (s & Qt::ShiftButton) ||
       (s & Qt::AltButton))
      return 0;
    else
      return 1;
  }

  void mousePressEvent(QMouseEvent *e)
  {
    if(e->button() == CGAL_QT_WIDGET_GET_POINT_BUTTON 
       && !firstpoint
       && is_pure(e->state()))
    {
      FT
	      x=static_cast<FT>(widget->x_real(e->x())),
	      y=static_cast<FT>(widget->y_real(e->y()));
      x1 = x;
      y1 = y;
      x2 = x;
      y2 = y;
      firstpoint = TRUE;
    } else if(e->button() == CGAL_QT_WIDGET_GET_POINT_BUTTON
       && is_pure(e->state())){
      FT
	      x=static_cast<FT>(widget->x_real(e->x())),
	      y=static_cast<FT>(widget->y_real(e->y()));
      if(x1!=x || y1!=y) {
        widget->new_object(make_object(Line(Point(x1,y1),Point(x,y))));
        firstpoint = FALSE;
      }    
    }
  }

  void leaveEvent(QEvent *e)
  {
    if(firstpoint)
    {
      RasterOp old_raster = widget->rasterOp();//save the initial raster mode
      QColor old_color = widget->color();
      widget->lock();
        widget->setRasterOp(XorROP);
        *widget << CGAL::GREEN;
        *widget << Line(Point(x1,y1),Point(x2,y2));
        widget->setRasterOp(old_raster);
        widget->setColor(old_color);
      widget->unlock();
      firsttime = true;
    }
  }
  void mouseMoveEvent(QMouseEvent *e)
  {
    if(firstpoint)
    {
      FT x=static_cast<FT>(widget->x_real(e->x()));
      FT y=static_cast<FT>(widget->y_real(e->y()));
      RasterOp old_raster = widget->rasterOp();//save the initial raster mode
      QColor old_color = widget->color();
      widget->setRasterOp(XorROP);
      widget->lock();
      *widget << CGAL::GREEN;
      if(!firsttime)
        *widget << Line(Point(x1,y1),Point(x2,y2));
      *widget << Line(Point(x1,y1),Point(x,y));
      widget->unlock();
      widget->setRasterOp(old_raster);
      widget->setColor(old_color);

      //save the last coordinates to redraw the screen
      x2 = x;
      y2 = y;
      firsttime = false;
    }
  };
  void activating()
  {
    oldcursor = widget->cursor();
    widget->setCursor(crossCursor);
  };

  void deactivating()
  {
    widget->setCursor(oldcursor);
    firstpoint = false;
  };

  FT	x1, //the X of the first point
	y1; //the Y of the first point
  FT	x2, //the old second point's X
	y2; //the old second point's Y
  bool	firstpoint, //true if the user left clicked once
	firsttime;  //true if the line is not drawn
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_GET_LINE_H
