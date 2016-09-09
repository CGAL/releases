// Copyright (c) 2002-2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/branches/CGAL-3.5-branch/Qt_widget/include/CGAL/IO/Qt_widget_show_mouse_coordinates.h $
// $Id: Qt_widget_show_mouse_coordinates.h 32795 2006-07-30 16:38:54Z spion $
// 
//
// Author(s)     : Radu Ursu

#ifndef CGAL_QT_WIDGET_SHOW_MOUSE_COORDINATES_H
#define CGAL_QT_WIDGET_SHOW_MOUSE_COORDINATES_H

#include <CGAL/IO/Qt_widget_layer.h>
#include <qobject.h>
#include <qmainwindow.h>
#include <qstatusbar.h>
#include <qstring.h>

namespace CGAL {

class Qt_widget_show_mouse_coordinates : public Qt_widget_layer
{
public:
	
  Qt_widget_show_mouse_coordinates(QMainWindow &mw, 
				   QObject* parent = 0,
				   const char* name = 0) 
    : Qt_widget_layer(parent, name), qmw(mw)
    {};

  void draw(){};
  void mouseMoveEvent(QMouseEvent *e)
  {
    QString s("x=%1 y=%2");
    double xcoord, ycoord;
    widget->x_real(e->x(), xcoord);
    widget->y_real(e->y(), ycoord);
    qmw.statusBar()->message(s.arg(xcoord, -20, 'g', 15).
			     arg(ycoord, -20,'g', 15));

  };
private:
  void deactivating(){
    qmw.statusBar()->clear();
  }
  QMainWindow	&qmw;
};//end class 

} // namespace CGAL

#endif // CGAL_QT_WIDGET_GET_SEGMENT_H
