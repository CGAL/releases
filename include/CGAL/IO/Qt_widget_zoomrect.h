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
// file          : include/CGAL/IO/Qt_widget_zoomrect.h
// package       : Qt_widget (1.2.30)
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

#ifndef CGAL_QT_WIDGET_ZOOMRECT_H
#define CGAL_QT_WIDGET_ZOOMRECT_H

#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include <qrect.h>
#include <qcursor.h>


#ifndef CGAL_QT_WIDGET_ZOOMRECT_BUTTON
#define CGAL_QT_WIDGET_ZOOMRECT_BUTTON Qt::LeftButton
#endif


namespace CGAL {

class Qt_widget_zoomrect : public Qt_widget_layer
{
public:
  int   first_x, first_y, x2, y2;
  bool  widgetrepainted;
  bool  on_first;

  Qt_widget_zoomrect() : widgetrepainted(TRUE), on_first(FALSE) {};

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

  void draw(){
    widgetrepainted = TRUE;
  };
  void mousePressEvent(QMouseEvent *e)
  {
    if(e->button() == CGAL_QT_WIDGET_ZOOMRECT_BUTTON
       && is_pure(e->state()))
    {
      if (!on_first)
      {
	      first_x = e->x();
        first_y = e->y();
        on_first = TRUE;
      }
    }
  };

  void mouseReleaseEvent(QMouseEvent *e)
  {
    if(e->button() == CGAL_QT_WIDGET_ZOOMRECT_BUTTON
       && is_pure(e->state()))
    {
      if((e->x() != first_x) && (e->y() != first_y)) {
        double x=widget->x_real(e->x());
	      double y=widget->y_real(e->y());
	      double xfirst2 = widget->x_real(first_x);
        double yfirst2 = widget->y_real(first_y);
  			
        double	xmin, xmax, ymin, ymax;
        if(x < xfirst2) {xmin = x; xmax = xfirst2;}
        else {xmin = xfirst2; xmax = x;};
        if(y < yfirst2) {ymin = y; ymax = yfirst2;}
        else {ymin = yfirst2; ymax = y;};

        widget->set_window(xmin, xmax, ymin, ymax);
        widget->redraw();
        on_first = FALSE;
      }
    }
  }
  void mouseMoveEvent(QMouseEvent *e)
  {
    if(on_first)
    {
      int
	      x = e->x(),
	      y = e->y();
			*widget << noFill;
      RasterOp old = widget->rasterOp();	//save the initial raster mode
      QColor old_color=widget->color();
      widget->setRasterOp(XorROP);
      widget->lock();
      widget->setColor(Qt::green);
      if(!widgetrepainted)
	      widget->get_painter().drawRect(first_x, first_y, 
										 x2 - first_x, y2 - first_y);
      widget->get_painter().drawRect(first_x, first_y, x - first_x,
									 y - first_y);
      widget->unlock();
      widget->setColor(old_color);
      widget->setRasterOp(old);

      //save the last coordinates to redraw the screen
      x2 = x;
      y2 = y;
      widgetrepainted = FALSE;
    }
  };

  void activating()
  {
    oldcursor = widget->cursor();
    widget->setCursor(crossCursor);
    widgetrepainted = TRUE;
  };

  void deactivating()
  {
    widget->setCursor(oldcursor);
		
    RasterOp old = widget->rasterOp();	//save the initial raster mode
    widget->setRasterOp(XorROP);
    widget->lock();
    *widget << CGAL::GREEN;
    widget->unlock();
    widget->setRasterOp(old);
  };
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_ZOOMRECT_H
