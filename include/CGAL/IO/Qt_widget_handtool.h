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
// file          : include/CGAL/IO/Qt_widget_handtool.h
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

#ifndef CGAL_QT_WIDGET_HANDTOOL_H
#define CGAL_QT_WIDGET_HANDTOOL_H


#include <cstdio>
#include <CGAL/IO/pixmaps/hand.xpm>
#include <CGAL/IO/pixmaps/holddown.xpm>
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_layer.h>
#include <qrect.h>
#include <qcursor.h>

#ifndef CGAL_QT_WIDGET_GET_POINT_BUTTON
#define CGAL_QT_WIDGET_GET_POINT_BUTTON Qt::LeftButton
#endif


namespace CGAL {

class Qt_widget_handtool : public Qt_widget_layer
{
public:
  Qt_widget_handtool() : wasrepainted(TRUE), on_first(FALSE){};

private:
  QCursor oldcursor;

  void draw(){
    wasrepainted = TRUE;
  };

  void timerEvent( QTimerEvent *e )
  {
    widget->setCursor(QCursor( 
              QPixmap( (const char**)hand_xpm)));
  }

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
       && is_pure(e->state()))
    {
      widget->setCursor(QCursor( QPixmap( (const char**)holddown_xpm)));
      if (!on_first){
	      first_x = e->x();
	      first_y = e->y();
	      on_first = TRUE;
      }	
    }
  };

  void mouseReleaseEvent(QMouseEvent *e)
  {
    if(e->button() == CGAL_QT_WIDGET_GET_POINT_BUTTON
       && is_pure(e->state()))
    {
      widget->setCursor(QCursor( QPixmap( (const char**)hand_xpm)));
      double
	      x=widget->x_real(e->x()),
	      y=widget->y_real(e->y()),
	      xfirst2 = widget->x_real(first_x),
	      yfirst2 = widget->y_real(first_y);
			
      double	xmin, xmax, ymin, ymax, distx, disty;
      if(x < xfirst2) {xmin = x; xmax = xfirst2;}
      else {xmin = xfirst2; xmax = x;};
      if(y < yfirst2) {ymin = y; ymax = yfirst2;}
      else {ymin = yfirst2; ymax = y;};
      distx = xfirst2 - x;
      disty = yfirst2 - y;
      widget->move_center(distx, disty);
      widget->redraw();
      on_first = FALSE;
    }
  }
  void mouseMoveEvent(QMouseEvent *e)
  {
    char tempc1[130], tempc2[40];
    if(on_first)
    {
      int x = e->x();
      int y = e->y();
      //save the initial raster mode
      RasterOp old = widget->rasterOp();	
      widget->setRasterOp(XorROP);
      widget->lock();
        *widget << CGAL::GRAY;
      if(!wasrepainted) {
        CGAL_CLIB_STD::sprintf(tempc1, " dx=%20.6f",
			widget->x_real(x2 - first_x));
        CGAL_CLIB_STD::sprintf(tempc2, ", dy=%20.6f",
			widget->x_real(y2 - first_y));
        strcat(tempc1, tempc2);
        widget->get_painter().drawLine(first_x, first_y, x2, y2);
        *widget << CGAL::GREEN;
        widget->get_painter().drawText(x2, y2, tempc1, 49);
        *widget << CGAL::GRAY;
      }
      CGAL_CLIB_STD::sprintf(tempc1, " dx=%20.6f",
		  widget->x_real(x - first_x));
      CGAL_CLIB_STD::sprintf(tempc2, ", dy=%20.6f",
		  widget->x_real(y - first_y));
      strcat(tempc1, tempc2);
      widget->get_painter().drawLine(first_x, first_y, x, y);
      *widget << CGAL::GREEN;
      widget->get_painter().drawText(x, y, tempc1, 49);
      widget->unlock();
      widget->setRasterOp(old);

      //save the last coordinates to redraw the screen
      x2 = x;
      y2 = y;
      wasrepainted = FALSE;
    }
  };

  void activating()
  {
    oldcursor = widget->cursor();
    widget->setCursor(QCursor( QPixmap( (const char**)hand_xpm)));
    wasrepainted = TRUE;
	  startTimer( 100 );
  };

  void deactivating()
  {
    widget->setCursor(oldcursor);
    killTimers();
  };

  int   first_x, first_y;
  int   x2, y2;
  bool	wasrepainted;
  bool	on_first;
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_HANDTOOL_H
