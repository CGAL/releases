// Copyright (c) 2002  Utrecht University (The Netherlands).
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
// $Source: /CVSROOT/CGAL/Packages/Polygon/demo/Polygon/polygon_2_toolbar.h,v $
// $Revision: 1.2.6.2 $ $Date: 2004/12/19 17:00:36 $
// $Name:  $
//
// Author(s)     : Radu Ursu


#ifndef CGAL_POLYGON_TOOLBAR_H
#define CGAL_POLYGON_TOOLBAR_H


#include "cgal_types.h"
#include <CGAL/IO/Qt_widget.h>
#include <CGAL/IO/Qt_widget_get_simple_polygon.h>
#include <CGAL/IO/Qt_widget_get_polygon.h>
#include <CGAL/IO/Qt_widget_get_point.h>

#include <qobject.h>
#include <qmainwindow.h>
#include <qtoolbutton.h>
#include <qtoolbar.h>
#include <qbuttongroup.h>

class Polygon_toolbar : public QToolBar
{
  Q_OBJECT
public:
  Polygon_toolbar(CGAL::Qt_widget *w, QMainWindow *mw);
	
private:
  QToolButton     *but[10];
  CGAL::Qt_widget *widget;
  QButtonGroup    *button_group;
  int             nr_of_buttons;
	
  CGAL::Qt_widget_get_simple_polygon<Cgal_Polygon> getsimplepoly;
  CGAL::Qt_widget_get_polygon<Cgal_Polygon>        getpoly;
  CGAL::Qt_widget_get_point<K>                     getpoint;
};//end class

#endif
